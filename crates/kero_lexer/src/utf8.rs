use anyhow::{anyhow, bail, Result};
use std::{collections::VecDeque, io::Read, str};

#[derive(Debug)]
pub enum UncheckedByteKind {
    Ascii,
    Continuation,
    FirstOf2ByteCodePoint,
    FirstOf3ByteCodePoint,
    FirstOf4ByteCodePoint,
    Unexpected,
}

pub fn get_unchecked_byte_kind(byte: u8) -> UncheckedByteKind {
    match byte {
        0x00..=0x7F => UncheckedByteKind::Ascii,
        0x80..=0xBF => UncheckedByteKind::Continuation,
        0xC0..=0xDF => UncheckedByteKind::FirstOf2ByteCodePoint,
        0xE0..=0xEF => UncheckedByteKind::FirstOf3ByteCodePoint,
        0xF0..=0xF7 => UncheckedByteKind::FirstOf4ByteCodePoint,
        _ => UncheckedByteKind::Unexpected,
    }
}

pub fn get_number_of_trailing_bytes(kind: UncheckedByteKind) -> usize {
    match kind {
        UncheckedByteKind::Ascii => 0,
        UncheckedByteKind::Continuation => 0,
        UncheckedByteKind::FirstOf2ByteCodePoint => 1,
        UncheckedByteKind::FirstOf3ByteCodePoint => 2,
        UncheckedByteKind::FirstOf4ByteCodePoint => 3,
        UncheckedByteKind::Unexpected => 0,
    }
}

pub struct Utf8UncheckedReader<R> {
    inner: R,
}

impl<R> Utf8UncheckedReader<R>
where
    R: Read,
{
    pub fn new(inner: R) -> Self {
        Self { inner }
    }

    pub fn read(&mut self, buf: &mut [u8; 4]) -> Result<usize> {
        buf.fill(0);
        let n = self.inner.read(&mut buf[0..1])?;
        if n == 0 {
            return Ok(0);
        }

        let first_byte = buf[0];
        let byte_kind = get_unchecked_byte_kind(first_byte);
        let num_trailing_bytes = match byte_kind {
            UncheckedByteKind::Continuation | UncheckedByteKind::Unexpected => {
                bail!(
                    "Invalid UTF-8 sequence. read unchecked byte kind: {:?}",
                    byte_kind
                );
            }
            UncheckedByteKind::Ascii
            | UncheckedByteKind::FirstOf2ByteCodePoint
            | UncheckedByteKind::FirstOf3ByteCodePoint
            | UncheckedByteKind::FirstOf4ByteCodePoint => get_number_of_trailing_bytes(byte_kind),
        };

        self.inner.read_exact(&mut buf[1..=num_trailing_bytes])?;
        Ok(num_trailing_bytes + 1)
    }
}

pub struct Utf8CharReader<R>
where
    R: Read,
{
    inner: Utf8UncheckedReader<R>,
}

impl<R> Utf8CharReader<R>
where
    R: Read,
{
    pub fn new(inner: R) -> Self {
        Self {
            inner: Utf8UncheckedReader::new(inner),
        }
    }

    pub fn read(&mut self) -> Result<Option<char>> {
        let mut buf = [0u8; 4];
        let n = self.inner.read(&mut buf)?;
        if n == 0 {
            return Ok(None);
        }

        let str = str::from_utf8(&buf[..=n])?;
        let mut chars = str.chars();
        let ch = chars
            .next()
            .ok_or_else(|| anyhow!("UTF-8 string must contain one character. str: {}", str))?;

        if chars.next().is_some() {
            bail!(
                "UTF-8 string must contain exactly one character. str: {}",
                str
            );
        }

        Ok(Some(ch))
    }
}

pub struct Utf8CharWindowBufReader<R>
where
    R: Read,
{
    inner: Utf8CharReader<R>,
    window_buf: VecDeque<char>,
}

impl<R> Utf8CharWindowBufReader<R>
where
    R: Read,
{
    pub fn new(inner: R) -> Self {
        Self {
            inner: Utf8CharReader::new(inner),
            window_buf: VecDeque::<char>::new(),
        }
    }

    pub fn read(&mut self, offset: usize) -> Result<Option<char>> {
        loop {
            if let Some(ch) = self.window_buf.get(offset).cloned() {
                return Ok(Some(ch));
            }

            let Some(ch) = self.inner.read()? else {
                return Ok(None);
            };

            self.window_buf.push_back(ch);
        }
    }

    pub fn pop(&mut self) -> Result<()> {
        self.window_buf
            .pop_front()
            .ok_or_else(|| anyhow!("Must be called when the element exists"));
        Ok(())
    }
}
