mod utf8;

use crate::utf8::unchecked::{CodePoint, LookaheadBufReader};
use anyhow::{bail, Result};
use kero_trie::Trie;
use std::{collections::VecDeque, io::Read};
use unicode_ident::is_xid_start;

#[derive(Debug, PartialEq)]
enum TokenKind {
    Endmarker,
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

#[derive(Debug)]
struct ReadLineContext {
    info_start_index: usize,
    line_start_offset: usize,
}

struct Lexer<'a, R>
where
    R: Read,
{
    keywords: &'a Trie<u8>,
    reader: LookaheadBufReader<R>,
    indent_stack: Vec<usize>,
    paren_count: usize,
    position: Position,
    info_queue: VecDeque<TokenInfo>,
    read_line_context: Option<ReadLineContext>,
}

impl<'a, R> Lexer<'a, R>
where
    R: Read,
{
    pub fn new(keywords: &'a Trie<u8>, reader: R) -> Lexer<'a, R> {
        Lexer {
            keywords,
            reader: LookaheadBufReader::new(reader),
            indent_stack: vec![0],
            paren_count: 0,
            position: Position::new(),
            info_queue: VecDeque::<TokenInfo>::new(),
            read_line_context: None,
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
        self.enter_read_line()?;

        if self.is_start_of_indent_or_dedent() {
            self.parse_indent_or_dedent()?;
        }

        loop {
            if self.is_start_of_endmarker()? {
                self.parse_endmarker()?;
                break;
            }

            if self.is_start_of_newline_or_nl()? {
                self.parse_newline_or_nl()?;
                break;
            }

            if self.is_start_of_name_or_keyword()? {
                self.parse_name_or_keyword()?;
            }
        }

        self.exit_read_line()?;
        Ok(())
    }

    fn enter_read_line(&mut self) -> Result<()> {
        if self.read_line_context.is_some() {
            bail!("Must not call enter_read_line more than once");
        }

        self.read_line_context = Some(ReadLineContext {
            info_start_index: self.info_queue.len(),
            line_start_offset: self.reader.offset(),
        });
        Ok(())
    }

    fn exit_read_line(&mut self) -> Result<()> {
        let Some(ctx) = &self.read_line_context else {
            bail!("Must call after enter_read_line");
        };

        for i in ctx.info_start_index..self.info_queue.len() {
            let Some(info) = self.info_queue.get_mut(i) else {
                bail!("Must have info present");
            };

            info.line_range.start = ctx.line_start_offset;
            info.line_range.end = self.reader.offset();
        }

        self.read_line_context = None;
        Ok(())
    }

    fn is_entered_read_line(&self) -> bool {
        self.read_line_context.is_some()
    }

    fn is_start_of_endmarker(&mut self) -> Result<bool> {
        let Some(_) = self.reader.lookahead(0)? else {
            return Ok(true);
        };

        Ok(false)
    }

    fn parse_endmarker(&mut self) -> Result<()> {
        debug_assert!(self.is_start_of_endmarker()?);

        self.push_info(
            TokenKind::Endmarker,
            self.reader.offset(),
            self.position.clone(),
        );
        Ok(())
    }

    fn is_start_of_indent_or_dedent(&self) -> bool {
        self.paren_count == 0
    }

    fn parse_indent_or_dedent(&mut self) -> Result<()> {
        debug_assert!(self.is_start_of_indent_or_dedent());

        let string_start = self.reader.offset();
        let position_start = self.position.clone();
        let mut space_count = 0;
        loop {
            let Some(point) = self.reader.lookahead(space_count)? else {
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

        for _ in 0..space_count {
            self.reader.advance(1)?;
        }

        if space_count > last_space_count {
            self.indent_stack.push(space_count);
            self.push_info(TokenKind::Indent, string_start, position_start)
        } else if space_count < last_space_count {
            let Some(_) = self.indent_stack.pop() else {
                bail!("Must have last indent present");
            };

            self.push_info(TokenKind::Dedent, string_start, position_start)
        }
        Ok(())
    }

    fn is_start_of_newline_or_nl(&mut self) -> Result<bool> {
        let Some(point) = self.reader.lookahead(0)? else {
            return Ok(false);
        };

        let CodePoint::B1(b) = point else {
            return Ok(false);
        };

        Ok(b == b'\r' || b == b'\n')
    }

    fn parse_newline_or_nl(&mut self) -> Result<()> {
        debug_assert!(self.is_start_of_newline_or_nl()?);

        let Some(point) = self.reader.lookahead(0)? else {
            bail!("Must have a point present");
        };

        let CodePoint::B1(b) = point else {
            bail!("Must be of type CodePoint::B1");
        };

        let string_start = self.reader.offset();
        let position_start = self.position.clone();

        self.position.line += 1;
        self.position.column = 0;
        self.reader.advance(1)?;

        if b == b'\r' {
            if let Some(next_point) = self.reader.lookahead(1)? {
                if let CodePoint::B1(next_byte) = next_point {
                    if next_byte == b'\n' {
                        self.reader.advance(1)?;
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

    fn is_start_of_name_or_keyword(&mut self) -> Result<bool> {
        let Some(point) = self.reader.lookahead(0)? else {
            return Ok(false);
        };

        match point {
            CodePoint::B1(b) => {
                Ok((b'a' <= b && b <= b'z') || (b'A' <= b && b <= b'Z') || b == b'_')
            }
            CodePoint::B2(_) | CodePoint::B3(_) | CodePoint::B4(_) => {
                let ch: char = point.try_into()?;
                Ok(is_xid_start(ch))
            }
        }
    }

    fn parse_name_or_keyword(&mut self) -> Result<()> {
        debug_assert!(self.is_start_of_name_or_keyword()?);
        todo!();
    }

    fn push_info(&mut self, kind: TokenKind, string_start: usize, position_start: Position) {
        debug_assert!(self.is_entered_read_line());

        self.info_queue.push_back(TokenInfo {
            kind,
            string_range: ByteRange {
                start: string_start,
                end: self.reader.offset(),
            },
            position_range: PositionRange {
                start: position_start,
                end: self.position.clone(),
            },
            line_range: ByteRange {
                start: 0, // set at exit_read_line
                end: 0,   // set at exit_read_line
            },
        });
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use kero_trie::TrieBuilder;

    #[test]
    fn endmarker() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        let result = lexer.next();
        let info = result.unwrap();
        assert!(info.kind == TokenKind::Endmarker);
        assert!(info.string_range.start == 0);
        assert!(info.string_range.end == 0);
        assert!(info.position_range.start.line == 1);
        assert!(info.position_range.start.column == 0);
        assert!(info.position_range.end.line == 1);
        assert!(info.position_range.end.column == 0);
        assert!(info.line_range.start == 0);
        assert!(info.line_range.end == 0);
    }

    #[test]
    fn nl_carriage_return() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        let result = lexer.next();
        let info = result.unwrap();
        assert!(info.kind == TokenKind::Nl);
        assert!(info.string_range.start == 0);
        assert!(info.string_range.end == 0);
        assert!(info.position_range.start.line == 1);
        assert!(info.position_range.start.column == 0);
        assert!(info.position_range.end.line == 1);
        assert!(info.position_range.end.column == 0);
        assert!(info.line_range.start == 0);
        assert!(info.line_range.end == 0);
    }

    #[test]
    fn nl_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        let result = lexer.next();
        let info = result.unwrap();
        assert!(info.kind == TokenKind::Nl);
        assert!(info.string_range.start == 0);
        assert!(info.string_range.end == 0);
        assert!(info.position_range.start.line == 1);
        assert!(info.position_range.start.column == 0);
        assert!(info.position_range.end.line == 1);
        assert!(info.position_range.end.column == 0);
        assert!(info.line_range.start == 0);
        assert!(info.line_range.end == 0);
    }

    #[test]
    fn nl_carriage_return_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        let result = lexer.next();
        let info = result.unwrap();
        assert!(info.kind == TokenKind::Nl);
        assert!(info.string_range.start == 0);
        assert!(info.string_range.end == 0);
        assert!(info.position_range.start.line == 1);
        assert!(info.position_range.start.column == 0);
        assert!(info.position_range.end.line == 1);
        assert!(info.position_range.end.column == 0);
        assert!(info.line_range.start == 0);
        assert!(info.line_range.end == 0);
    }
}
