pub mod unchecked {
    use anyhow::{anyhow, bail, Result};
    use core::{slice, str};
    use std::{collections::VecDeque, io::Read};

    #[derive(Debug)]
    pub enum ByteKind {
        Ascii,
        Continuation,
        FirstOf2ByteCodePoint,
        FirstOf3ByteCodePoint,
        FirstOf4ByteCodePoint,
        Unexpected,
    }

    pub fn get_byte_kind(byte: u8) -> ByteKind {
        match byte {
            0x00..=0x7F => ByteKind::Ascii,
            0x80..=0xBF => ByteKind::Continuation,
            0xC0..=0xDF => ByteKind::FirstOf2ByteCodePoint,
            0xE0..=0xEF => ByteKind::FirstOf3ByteCodePoint,
            0xF0..=0xF7 => ByteKind::FirstOf4ByteCodePoint,
            _ => ByteKind::Unexpected,
        }
    }

    pub fn get_trailing_byte_count(kind: ByteKind) -> usize {
        match kind {
            ByteKind::Ascii => 0,
            ByteKind::Continuation => 0,
            ByteKind::FirstOf2ByteCodePoint => 1,
            ByteKind::FirstOf3ByteCodePoint => 2,
            ByteKind::FirstOf4ByteCodePoint => 3,
            ByteKind::Unexpected => 0,
        }
    }

    #[derive(Debug, Clone)]
    pub enum CodePoint {
        B1(u8),
        B2([u8; 2]),
        B3([u8; 3]),
        B4([u8; 4]),
    }

    impl CodePoint {
        pub fn len(&self) -> usize {
            match self {
                Self::B1(_) => 1,
                Self::B2(_) => 2,
                Self::B3(_) => 3,
                Self::B4(_) => 4,
            }
        }

        pub fn try_to_char(&self) -> Result<char> {
            let bytes: &[u8] = match &self {
                CodePoint::B1(b) => slice::from_ref(&b),
                CodePoint::B2(bs) => bs,
                CodePoint::B3(bs) => bs,
                CodePoint::B4(bs) => bs,
            };

            let str = str::from_utf8(&bytes)?;
            let mut chars = str.chars();
            let Some(c) = chars.next() else {
                bail!("Must contain at least one element. str: {}", str);
            };

            if chars.next().is_some() {
                bail!("Must contain exactly one element. str: {}", str);
            }

            return Ok(c);
        }
    }

    impl TryFrom<CodePoint> for char {
        type Error = anyhow::Error;

        fn try_from(point: CodePoint) -> Result<char> {
            point.try_to_char()
        }
    }

    pub struct Reader<R> {
        inner: R,
    }

    impl<R> Reader<R>
    where
        R: Read,
    {
        pub fn new(inner: R) -> Self {
            Self { inner }
        }

        pub fn read(&mut self) -> Result<Option<CodePoint>> {
            let mut buf = [0u8; 4];
            let n = self.inner.read(&mut buf[0..1])?;
            if n == 0 {
                return Ok(None);
            }

            let first = buf[0];
            let kind = get_byte_kind(first);
            let trailing_byte_count = match kind {
                ByteKind::Continuation | ByteKind::Unexpected => {
                    bail!("Unexpected byte kind. read byte kind: {:?}", kind);
                }
                ByteKind::Ascii
                | ByteKind::FirstOf2ByteCodePoint
                | ByteKind::FirstOf3ByteCodePoint
                | ByteKind::FirstOf4ByteCodePoint => get_trailing_byte_count(kind),
            };

            self.inner.read_exact(&mut buf[1..=trailing_byte_count])?;

            let code_point = match trailing_byte_count {
                0 => CodePoint::B1(buf[0]),
                1 => CodePoint::B2([buf[0], buf[1]]),
                2 => CodePoint::B3([buf[0], buf[1], buf[2]]),
                3 => CodePoint::B4([buf[0], buf[1], buf[2], buf[3]]),
                _ => bail!(
                    "Unexpected trailing byte count. trailing byte count: {}",
                    trailing_byte_count
                ),
            };
            Ok(Some(code_point))
        }
    }

    pub struct LookaheadBufReader<R> {
        inner: Reader<R>,
        buf: VecDeque<CodePoint>,
        offset: usize,
    }

    impl<R> LookaheadBufReader<R>
    where
        R: Read,
    {
        pub fn new(inner: R) -> Self {
            Self {
                inner: Reader::new(inner),
                buf: VecDeque::<CodePoint>::new(),
                offset: 0,
            }
        }

        pub fn lookahead(&mut self, offset: usize) -> Result<Option<CodePoint>> {
            loop {
                if let Some(point) = self.buf.get(offset) {
                    return Ok(Some(point.clone()));
                }

                let Some(point) = self.inner.read()? else {
                    return Ok(None);
                };

                self.buf.push_back(point);
            }
        }

        pub fn advance(&mut self, amount: usize) -> Result<()> {
            if amount > self.buf.len() {
                bail!("Must be less than or equal to the length of the buffer");
            }

            for _ in 0..amount {
                let Some(point) = self.buf.pop_front() else {
                    bail!("Must contain the element");
                };

                self.offset += point.len();
            }
            Ok(())
        }

        pub fn offset(&self) -> usize {
            self.offset
        }
    }
}

pub mod checked {
    use super::unchecked::Reader;
    use anyhow::Result;
    use std::io::Read;

    pub struct CharReader<R>
    where
        R: Read,
    {
        inner: Reader<R>,
    }

    impl<R> CharReader<R>
    where
        R: Read,
    {
        pub fn new(inner: R) -> Self {
            Self {
                inner: Reader::new(inner),
            }
        }

        pub fn read(&mut self) -> Result<Option<char>> {
            let Some(point) = self.inner.read()? else {
                return Ok(None);
            };

            let ch: char = point.try_into()?;
            Ok(Some(ch))
        }
    }
}
