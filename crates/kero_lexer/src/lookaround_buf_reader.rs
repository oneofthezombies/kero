use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read};

use crate::circular_buffer::CircularBuffer;

const DEFAULT_LOOKBEHIND_CAPACITY: usize = 0;

pub struct LookaroundBufReader<R> {
    inner: R,
    buf: CircularBuffer<5, u8>,
    absolute_offset: usize,
    lookbehind_capacity: usize,
    lookbehind_length: usize,
    is_eof: bool,
}

impl<R> LookaroundBufReader<R>
where
    R: Read,
{
    pub fn new(inner: R) -> Result<Self> {
        Self::with_lookbehind_capacity(inner, DEFAULT_LOOKBEHIND_CAPACITY)
    }

    pub fn with_lookbehind_capacity(inner: R, lookbehind_capacity: usize) -> Result<Self> {
        Ok(Self {
            inner,
            buf: CircularBuffer::<5, u8>::try_new()?,
            absolute_offset: 0,
            lookbehind_capacity,
            lookbehind_length: 0,
            is_eof: false,
        })
    }

    pub fn read(&mut self, relative_offset: isize) -> Result<Option<u8>> {
        let index = self.parse_relative_offset(relative_offset)?;
        loop {
            if let Some(v) = self.buf.get(index) {
                return Ok(Some(v.clone()));
            }

            if self.is_eof {
                return Ok(None);
            }

            let mut buf = [0u8; 4];
            let need_count = index + 1 - self.buf.len();
            if need_count > 4 {
                bail!("read buffer out of range");
            }
            let read_count = self.inner.read(&mut buf[0..need_count])?;
            if read_count == 0 {
                self.is_eof = true;
                return Ok(None);
            }

            for i in 0..read_count {
                if !self.buf.push_back(buf[i]) {
                    bail!("circular buffer out of range");
                }
            }
        }
    }

    pub fn advance(&mut self, offset: isize) -> Result<()> {
        if offset >= 0 {
            if offset as usize > self.lookahead_length() {
                bail!("Must be less than or equal to the lookahead length");
            }

            for _ in 0..offset {
                if self.lookbehind_length == self.lookbehind_capacity {
                    let Some(_) = self.buf.pop_front() else {
                        bail!("Must contain the element");
                    };
                } else if self.lookbehind_length < self.lookbehind_capacity {
                    self.lookbehind_length += 1;
                }

                self.absolute_offset += 1;
            }
        } else {
            let amount = offset.abs() as usize;
            if amount > self.lookbehind_length {
                bail!("Must be less than or equal to the lookbehind length");
            }

            for _ in 0..amount {
                self.lookbehind_length -= 1;
                self.absolute_offset -= 1;
            }
        }

        Ok(())
    }

    fn parse_relative_offset(&self, relative_offset: isize) -> Result<usize> {
        let Some(v) = self.lookbehind_length.checked_add_signed(relative_offset) else {
            bail!(
                "Overflow occurred. lookbehind_length: {} relative_offset: {}",
                self.lookbehind_length,
                relative_offset
            );
        };

        Ok(v)
    }

    pub fn absolute_offset(&self) -> usize {
        self.absolute_offset
    }

    pub fn lookbehind_length(&self) -> usize {
        self.lookbehind_length
    }

    pub fn lookbehind_capacity(&self) -> usize {
        self.lookbehind_capacity
    }

    pub fn lookahead_length(&self) -> usize {
        self.buf.len() - self.lookbehind_length
    }

    pub fn buffer_length(&self) -> usize {
        self.buf.len()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn eof_greater_1() {
        let source = b"";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        let result = reader.read(0);
        assert!(result.unwrap().is_none());
        assert!(reader.buffer_length() == 0);
        assert!(reader.lookahead_length() == 0);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn eof_greater_2() {
        let source = b"";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        let result = reader.read(1);
        assert!(result.unwrap().is_none());
        assert!(reader.buffer_length() == 0);
        assert!(reader.lookahead_length() == 0);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn eof_multiple_read() {
        let source = b"";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().is_none());
        }
        {
            let result = reader.read(0);
            assert!(result.unwrap().is_none());
        }
        assert!(reader.buffer_length() == 0);
        assert!(reader.lookahead_length() == 0);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn read() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        let result = reader.read(0);
        assert!(result.unwrap().unwrap() == b'a');
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn read_multiple() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn read_greater_1() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        let result = reader.read(1);
        assert!(result.unwrap().is_none());
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn read_greater_2() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        let result = reader.read(2);
        assert!(result.unwrap().is_none());
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn advance_0() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.advance(0);
            assert!(result.is_ok());
        }
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn advance_1() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.advance(1);
            assert!(result.is_ok());
        }
        {
            let result = reader.read(0);
            assert!(result.unwrap().is_none());
        }
        assert!(reader.buffer_length() == 0);
        assert!(reader.lookahead_length() == 0);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 1);
    }

    #[test]
    fn advance_2() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.advance(2);
            assert!(result.is_err());
        }
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn advance_minus_1() {
        let source = b"a";
        let mut reader = LookaroundBufReader::new(source.as_slice()).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.advance(-1);
            assert!(result.is_err());
        }
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 0);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }

    #[test]
    fn lookbehind_advance_1() {
        let source = b"a";
        let mut reader =
            LookaroundBufReader::with_lookbehind_capacity(source.as_slice(), 1).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.advance(1);
            assert!(result.is_ok());
        }
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 0);
        assert!(reader.lookbehind_capacity() == 1);
        assert!(reader.lookbehind_length() == 1);
        assert!(reader.absolute_offset() == 1);
    }

    #[test]
    fn lookbehind_advance_1_advance_minus_1() {
        let source = b"a";
        let mut reader =
            LookaroundBufReader::with_lookbehind_capacity(source.as_slice(), 1).unwrap();
        {
            let result = reader.read(0);
            assert!(result.unwrap().unwrap() == b'a');
        }
        {
            let result = reader.advance(1);
            assert!(result.is_ok());
        }
        {
            let result = reader.advance(-1);
            assert!(result.is_ok());
        }
        assert!(reader.buffer_length() == 1);
        assert!(reader.lookahead_length() == 1);
        assert!(reader.lookbehind_capacity() == 1);
        assert!(reader.lookbehind_length() == 0);
        assert!(reader.absolute_offset() == 0);
    }
}
