mod utf8;
mod utils;

use std::{collections::VecDeque, io::Read};

use anyhow::{anyhow, bail, Result};
use kero_trie::Trie;
use utf8::unchecked::{CodePoint, Reader};

#[derive(Debug, PartialEq)]
enum TokenKind {
    Eof,
    Newline,
    Nl,
    Indent,
    Dedent,
    // Identifier,
    // Number,
    // String,

    // // Keywords
    // As,     // as
    // From,   // from
    // Import, // import
    // True,   // True
    // False,  // False
    // None,   // None

    // // Symbols
    // Asterisk, // *
    // Colon,    // :
    // Equal,    // =
    // LParen,   // (
    // RParen,   // )
    // Minus,    // -
    // Plus,     // +
}

#[derive(Debug)]
struct ByteRange {
    start: usize, // inclusive
    end: usize,   // exclusive
}

#[derive(Debug, Clone)]
struct Position {
    line: usize,
    column: usize,
}

impl Position {
    fn new() -> Self {
        Self { line: 1, column: 0 }
    }
}

#[derive(Debug, Clone)]
struct PositionRange {
    start: Position, // inclusive
    end: Position,   // exclusive
}

#[derive(Debug)]
struct TokenInfo {
    kind: TokenKind,
    string_range: ByteRange,
    position_range: PositionRange,
    line_range: ByteRange,
}

struct Lexer<'a, R>
where
    R: Read,
{
    keywords: &'a Trie<char>,
    reader: Reader<R>,
    indent_stack: Vec<usize>,
    paren_count: usize,
    byte_offset: usize,
    position: Position,
    point_queue: VecDeque<CodePoint>,
    info_queue: VecDeque<TokenInfo>,
}

impl<'a, R> Lexer<'a, R>
where
    R: Read,
{
    pub fn new(keywords: &'a Trie<char>, reader: R) -> Lexer<'a, R> {
        Lexer {
            keywords,
            reader: Reader::new(reader),
            indent_stack: vec![0],
            paren_count: 0,
            position: Position::new(),
            info_queue: VecDeque::<TokenInfo>::new(),
            byte_offset: 0,
            point_queue: VecDeque::<CodePoint>::new(),
        }
    }

    pub fn next(&mut self) -> Result<TokenInfo> {
        loop {
            if let Some(info) = self.info_queue.pop_front() {
                return Ok(info);
            }

            self.read_line()?;
        }
    }

    fn read_line(&mut self) -> Result<()> {
        let line_start = self.byte_offset;
        let info_start_index = self.info_queue.len();
        if self.paren_count == 0 {
            self.process_indent_or_dedent()?;
        }

        loop {
            let Some(point) = self.lookahead(0)? else {
                self.push_info(TokenKind::Eof, self.byte_offset, self.position.clone());
                break;
            };

            match point {
                CodePoint::B1(b) => {
                    if b == b'\r' || b == b'\n' {
                        self.process_newline_or_nl(b)?;
                        break;
                    } else if (b'a' <= b && b <= b'z') || (b'A' <= b && b <= b'Z') || b == b'_' {
                        self.process_name_or_keyword(b)?;
                    }
                }
                CodePoint::B2(bs) => self.process_name(&bs)?,
                CodePoint::B3(bs) => self.process_name(&bs)?,
                CodePoint::B4(bs) => self.process_name(&bs)?,
            }
        }

        self.process_line_range(info_start_index, line_start)?;
        Ok(())
    }

    fn process_line_range(&mut self, info_start_index: usize, line_start: usize) -> Result<()> {
        for i in info_start_index..self.info_queue.len() {
            let Some(info) = self.info_queue.get_mut(i) else {
                bail!("Must have info present");
            };

            info.line_range.start = line_start;
            info.line_range.end = self.byte_offset;
        }
        Ok(())
    }

    fn process_name_or_keyword(&mut self, byte: u8) -> Result<()> {
        debug_assert!(
            (b'a' <= byte && byte <= b'z') || (b'A' <= byte && byte <= b'Z') || byte == b'_'
        );
        todo!();
    }

    fn process_name(&mut self, bytes: &[u8]) -> Result<()> {
        todo!();
    }

    fn process_indent_or_dedent(&mut self) -> Result<()> {
        debug_assert!(self.paren_count == 0);

        let string_start = self.byte_offset;
        let position_start = self.position.clone();
        let mut space_count = 0;
        loop {
            let Some(point) = self.lookahead(space_count)? else {
                break;
            };

            let CodePoint::B1(b) = point else {
                break;
            };

            if b != b' ' {
                break;
            }

            space_count += 1;
        }

        let Some(last_space_count) = self.indent_stack.last().cloned() else {
            bail!("Must have last indent present");
        };

        for _ in 0..=space_count {
            self.consume()?;
        }

        if space_count > last_space_count {
            self.indent_stack.push(space_count);
            self.push_info(TokenKind::Indent, string_start, position_start);
        } else if space_count < last_space_count {
            let Some(_) = self.indent_stack.pop() else {
                bail!("Must have last indent present");
            };

            self.push_info(TokenKind::Dedent, string_start, position_start);
        }

        Ok(())
    }

    fn process_newline_or_nl(&mut self, byte: u8) -> Result<()> {
        debug_assert!(byte == b'\r' || byte == b'\n');

        let string_start = self.byte_offset;
        let position_start = self.position.clone();

        self.position.line += 1;
        self.position.column = 0;
        self.consume()?;

        if byte == b'\r' {
            if let Some(next_point) = self.lookahead(1)? {
                if let CodePoint::B1(next_byte) = next_point {
                    if next_byte == b'\n' {
                        self.consume()?;
                    }
                }
            }
        }

        self.push_info(
            if self.paren_count > 0 {
                TokenKind::Nl
            } else {
                TokenKind::Newline
            },
            string_start,
            position_start,
        );
        Ok(())
    }

    fn push_info(&mut self, kind: TokenKind, string_start: usize, position_start: Position) {
        self.info_queue.push_back(TokenInfo {
            kind,
            string_range: ByteRange {
                start: string_start,
                end: self.byte_offset,
            },
            position_range: PositionRange {
                start: position_start,
                end: self.position.clone(),
            },
            line_range: ByteRange {
                start: 0, // set at the end of read_line
                end: 0,   // set at the end of read_line
            },
        });
    }

    fn lookahead(&mut self, offset: usize) -> Result<Option<CodePoint>> {
        loop {
            if let Some(point) = self.point_queue.get(offset) {
                return Ok(Some(point.clone()));
            }

            let Some(point) = self.reader.read()? else {
                return Ok(None);
            };

            self.point_queue.push_back(point);
        }
    }

    fn consume(&mut self) -> Result<()> {
        let Some(point) = self.point_queue.pop_front() else {
            bail!("Must be called when there is an point");
        };

        self.byte_offset += point.len();
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use kero_trie::TrieBuilder;

    use super::*;

    #[test]
    fn test_lexer() {}
}
