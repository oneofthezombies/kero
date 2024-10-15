use anyhow::{anyhow, bail, Result};
use std::{collections::VecDeque, io::Read, str};

#[derive(Debug)]
enum UncheckedByteKind {
    Ascii,
    Continuation,
    FirstOf2ByteCodePoint,
    FirstOf3ByteCodePoint,
    FirstOf4ByteCodePoint,
    Unexpected,
}

fn get_unchecked_byte_kind(byte: u8) -> UncheckedByteKind {
    match byte {
        0x00..=0x7F => UncheckedByteKind::Ascii,
        0x80..=0xBF => UncheckedByteKind::Continuation,
        0xC0..=0xDF => UncheckedByteKind::FirstOf2ByteCodePoint,
        0xE0..=0xEF => UncheckedByteKind::FirstOf3ByteCodePoint,
        0xF0..=0xF7 => UncheckedByteKind::FirstOf4ByteCodePoint,
        _ => UncheckedByteKind::Unexpected,
    }
}

fn get_number_of_trailing_bytes(kind: UncheckedByteKind) -> usize {
    match kind {
        UncheckedByteKind::Ascii => 0,
        UncheckedByteKind::Continuation => 0,
        UncheckedByteKind::FirstOf2ByteCodePoint => 1,
        UncheckedByteKind::FirstOf3ByteCodePoint => 2,
        UncheckedByteKind::FirstOf4ByteCodePoint => 3,
        UncheckedByteKind::Unexpected => 0,
    }
}

fn read_utf8_char<R>(reader: &mut R) -> Result<Option<char>>
where
    R: Read,
{
    let mut buffer = [0u8, 4];
    let n = reader.read(&mut buffer[0..1])?;
    if n == 0 {
        return Ok(None);
    }

    let first_byte = buffer[0];
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
    reader.read_exact(&mut buffer[1..=num_trailing_bytes])?;

    let str = str::from_utf8(&buffer[..=num_trailing_bytes])?;
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

pub struct Utf8CharWindowBufReader<R> {
    inner: R,
    window_buf: VecDeque<char>,
}

impl<R> Utf8CharWindowBufReader<R>
where
    R: Read,
{
    pub fn new(inner: R) -> Self {
        Self {
            inner,
            window_buf: VecDeque::<char>::new(),
        }
    }

    pub fn get(&mut self, offset: usize) -> Result<Option<char>> {
        loop {
            if let Some(ch) = self.window_buf.get(offset).cloned() {
                return Ok(Some(ch));
            }

            let Some(ch) = read_utf8_char(&mut self.inner)? else {
                return Ok(None);
            };

            self.window_buf.push_back(ch);
        }
    }

    pub fn pop_left(&mut self) -> Result<()> {
        self.window_buf
            .pop_front()
            .ok_or_else(|| anyhow!("Must be called when the element exists"));
        Ok(())
    }
}
