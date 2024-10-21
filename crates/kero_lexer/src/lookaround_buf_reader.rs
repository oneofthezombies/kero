use crate::circular_buffer::CircularBuffer;
use anyhow::{bail, Result};
use std::io::Read;

const DEFAULT_LOOKBEHIND_CAPACITY: usize = 0;

pub struct LookaroundBufReader<R, const N: usize> {
    inner: R,
    buf: CircularBuffer<u8, N>,
    absolute_offset: usize,
    lookbehind_capacity: usize,
    lookbehind_length: usize,
    is_eof: bool,
}

impl<R, const N: usize> LookaroundBufReader<R, N>
where
    R: Read,
{
    pub fn new(inner: R) -> Result<Self> {
        Self::with_lookbehind_capacity(inner, DEFAULT_LOOKBEHIND_CAPACITY)
    }

    pub fn with_lookbehind_capacity(inner: R, lookbehind_capacity: usize) -> Result<Self> {
        let buf = CircularBuffer::<u8, N>::try_new()?;
        if lookbehind_capacity > N - 1 {
            bail!(
                "lookbehind_capacity must be less than N - 1 for current lookahead(0). lookbehind_capacity: {} N: {}",
                lookbehind_capacity,
                N
            );
        }
        Ok(Self {
            inner,
            buf,
            absolute_offset: 0,
            lookbehind_capacity,
            lookbehind_length: 0,
            is_eof: false,
        })
    }

    pub fn read(&mut self, relative_offset: isize) -> Result<Option<u8>> {
        let Some(index) = self.lookbehind_length.checked_add_signed(relative_offset) else {
            bail!(
                "Overflow occurred. lookbehind_length: {} relative_offset: {}",
                self.lookbehind_length,
                relative_offset
            );
        };
        if index >= self.buf.capacity() {
            bail!(
                "Index must be less than buffer capacity. index: {} capacity: {}",
                index,
                self.buf.capacity()
            );
        }
        loop {
            if let Some(v) = self.buf.get(index) {
                return Ok(Some(v.clone()));
            }
            if self.is_eof {
                return Ok(None);
            }
            let need_len = index + 1 - self.buf.len();
            let mut read_buf = [0u8; N];
            let read_len = self.inner.read(&mut read_buf[0..need_len])?;
            if read_len == 0 {
                self.is_eof = true;
                return Ok(None);
            }
            for i in 0..read_len {
                if !self.buf.push_back(read_buf[i]) {
                    bail!("InternalError: It must be verified early in the function");
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
        let mut reader = LookaroundBufReader::<_, 5>::new(source.as_slice()).unwrap();
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
            LookaroundBufReader::<_, 5>::with_lookbehind_capacity(source.as_slice(), 1).unwrap();
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
            LookaroundBufReader::<_, 5>::with_lookbehind_capacity(source.as_slice(), 1).unwrap();
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
