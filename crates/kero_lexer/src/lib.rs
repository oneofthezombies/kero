mod lookaround_buf_reader;
mod utf8;

use anyhow::{bail, Result};
use kero_trie::Trie;
use lookaround_buf_reader::LookaroundBufReader;
use std::{collections::VecDeque, io::Read};
use unicode_ident::is_xid_start;

#[derive(Debug, PartialEq)]
enum TokenKind {
    Endmarker, // EOF
    Newline,
    Nl,
    Indent,
    Dedent,
    Comment, // #
}

#[derive(Debug)]
struct ByteRange {
    start: usize, // inclusive
    end: usize,   // exclusive
}

#[derive(Debug, Clone, PartialEq)]
struct Position {
    line: usize,
    column: usize,
}

impl Position {
    fn new() -> Self {
        Self { line: 1, column: 0 }
    }
}

#[derive(Debug)]
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

type TokenInfoPtr = Box<TokenInfo>;

#[derive(Debug)]
struct LineContext {
    info_start_index: usize,
    line_start_offset: usize,
    column: usize,
    is_processed_nl_or_newline: bool,
    is_processed_name_or_string: bool,
}

#[derive(Debug)]
struct StringContext {
    string_start_offset: usize,
    position_start: Position,
}

struct Lexer<'a, R>
where
    R: Read,
{
    keywords: &'a Trie<u8>,
    reader: LookaroundBufReader<R>,
    info_queue: VecDeque<TokenInfoPtr>,
    indent_stack: Vec<usize>,
    bracket_level: usize,
    line: usize,
    is_processed_endmarker: bool,
}

impl<'a, R> Lexer<'a, R>
where
    R: Read,
{
    pub fn new(keywords: &'a Trie<u8>, reader: R) -> Lexer<'a, R> {
        Lexer {
            keywords,
            reader: LookaroundBufReader::with_lookbehind_capacity(reader, 1),
            indent_stack: vec![0],
            bracket_level: 0,
            line: 1,
            info_queue: VecDeque::<TokenInfoPtr>::new(),
            is_processed_endmarker: false,
        }
    }

    pub fn next(&mut self) -> Result<TokenInfoPtr> {
        loop {
            if let Some(info) = self.info_queue.pop_front() {
                return Ok(info);
            }

            if self.is_processed_endmarker {
                bail!("All tokens have already been processed");
            }

            self.parse_line()?;
        }
    }

    fn parse_line(&mut self) -> Result<()> {
        let mut line_ctx = self.create_line_context();
        loop {
            if self.is_start_of_endmarker()? {
                self.process_endmarker(&mut line_ctx)?;
                break;
            } else if self.is_start_of_nl_or_newline()? {
                self.process_nl_or_newline(&mut line_ctx)?;
                break;
            } else {
                todo!();
            }
        }
        self.update_line_range_end(&line_ctx)?;
        Ok(())
    }

    fn create_line_context(&self) -> LineContext {
        LineContext {
            info_start_index: self.info_queue.len(),
            line_start_offset: self.reader.get_total_offset(),
            column: 0,
            is_processed_name_or_string: false,
            is_processed_nl_or_newline: false,
        }
    }

    fn create_string_context(&self, line_ctx: &LineContext) -> StringContext {
        StringContext {
            string_start_offset: self.reader.get_total_offset(),
            position_start: Position {
                line: self.line,
                column: line_ctx.column,
            },
        }
    }

    fn update_line_range_end(&mut self, line_ctx: &LineContext) -> Result<()> {
        for i in line_ctx.info_start_index..self.info_queue.len() {
            let Some(info) = self.info_queue.get_mut(i) else {
                bail!("Must have a info present");
            };
            info.line_range.end = self.reader.get_total_offset();
        }
        Ok(())
    }

    fn push_info(&mut self, line_ctx: &LineContext, str_ctx: &StringContext, kind: TokenKind) {
        self.info_queue.push_back(Box::new(TokenInfo {
            kind,
            string_range: ByteRange {
                start: str_ctx.string_start_offset,
                end: self.reader.get_total_offset(),
            },
            position_range: PositionRange {
                start: str_ctx.position_start.clone(),
                end: Position {
                    line: self.line,
                    column: line_ctx.column,
                },
            },
            line_range: ByteRange {
                start: line_ctx.line_start_offset,
                end: 0, // set on update_line_range_end
            },
        }));
    }

    fn is_start_of_endmarker(&mut self) -> Result<bool> {
        let Some(_) = self.reader.read(0)? else {
            return Ok(true);
        };

        Ok(false)
    }

    fn process_endmarker(&mut self, line_ctx: &mut LineContext) -> Result<()> {
        debug_assert!(self.is_start_of_endmarker()?);

        let has_info_in_line = line_ctx.line_start_offset < self.info_queue.len();
        if has_info_in_line {
            if !line_ctx.is_processed_nl_or_newline {
                line_ctx.column += 1;
                let str_ctx = self.create_string_context(line_ctx);
                self.push_info(
                    &line_ctx,
                    &str_ctx,
                    if line_ctx.is_processed_name_or_string {
                        TokenKind::Newline
                    } else {
                        TokenKind::Nl
                    },
                );
                self.line += 1;
            }
        }

        let str_ctx = self.create_string_context(line_ctx);
        self.push_info(&line_ctx, &str_ctx, TokenKind::Endmarker);
        self.is_processed_endmarker = true;
        Ok(())
    }

    // fn is_start_of_indent_or_dedent(&self) -> bool {
    //     self.paren_count == 0
    // }

    // fn parse_indent_or_dedent(&mut self) -> Result<()> {
    //     debug_assert!(self.is_start_of_indent_or_dedent());

    //     let string_start = self.reader.get_total_offset();
    //     let position_start = self.position.clone();
    //     let mut space_count = 0;
    //     loop {
    //         let Some(point) = self.reader.read(space_count)? else {
    //             break;
    //         };

    //         let CodePoint::B1(b) = point else {
    //             break;
    //         };

    //         if b != b' ' {
    //             break;
    //         }

    //         space_count += 1;
    //     }

    //     let Some(last_space_count) = self.indent_stack.last().cloned() else {
    //         bail!("Must have last indent present");
    //     };

    //     for _ in 0..space_count {
    //         self.reader.advance(1)?;
    //     }

    //     if space_count > last_space_count {
    //         self.indent_stack.push(space_count);
    //         self.push_info(TokenKind::Indent, string_start, position_start)
    //     } else if space_count < last_space_count {
    //         let Some(_) = self.indent_stack.pop() else {
    //             bail!("Must have last indent present");
    //         };

    //         self.push_info(TokenKind::Dedent, string_start, position_start)
    //     }
    //     Ok(())
    // }

    fn is_start_of_nl_or_newline(&mut self) -> Result<bool> {
        let Some(current) = self.reader.read(0)? else {
            return Ok(false);
        };

        Ok(current == b'\r' || current == b'\n')
    }

    fn process_nl_or_newline(&mut self, line_ctx: &mut LineContext) -> Result<()> {
        debug_assert!(self.is_start_of_nl_or_newline()?);

        let Some(current) = self.reader.read(0)? else {
            bail!("Must have a byte present");
        };

        let str_ctx = self.create_string_context(line_ctx);
        self.reader.advance(1)?;
        line_ctx.column += 1;

        if current == b'\r' {
            if let Some(next) = self.reader.read(1)? {
                if next == b'\n' {
                    self.reader.advance(1)?;
                    line_ctx.column += 1;
                }
            }
        }

        self.push_info(
            &line_ctx,
            &str_ctx,
            if line_ctx.is_processed_name_or_string {
                TokenKind::Newline
            } else {
                TokenKind::Nl
            },
        );
        self.line += 1;
        Ok(())
    }

    // fn is_start_of_name_or_keyword(&mut self) -> Result<bool> {
    //     let Some(point) = self.reader.lookahead(0)? else {
    //         return Ok(false);
    //     };

    //     match point {
    //         CodePoint::B1(b) => {
    //             Ok((b'a' <= b && b <= b'z') || (b'A' <= b && b <= b'Z') || b == b'_')
    //         }
    //         CodePoint::B2(_) | CodePoint::B3(_) | CodePoint::B4(_) => {
    //             let ch: char = point.try_into()?;
    //             Ok(is_xid_start(ch))
    //         }
    //     }
    // }

    // fn parse_name_or_keyword(&mut self) -> Result<()> {
    //     debug_assert!(self.is_start_of_name_or_keyword()?);
    //     todo!();
    // }
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
        let source = b"\r";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let result = lexer.next();
            let info = result.unwrap();
            assert!(info.kind == TokenKind::Nl);
            assert!(info.string_range.start == 0);
            assert!(info.string_range.end == 1);
            assert!(info.position_range.start.line == 1);
            assert!(info.position_range.start.column == 0);
            assert!(info.position_range.end.line == 1);
            assert!(info.position_range.end.column == 1);
            assert!(info.line_range.start == 0);
            assert!(info.line_range.end == 1);
        }
        {
            let result = lexer.next();
            let info = result.unwrap();
            assert!(info.kind == TokenKind::Endmarker);
            assert!(info.string_range.start == 1);
            assert!(info.string_range.end == 1);
            assert!(info.position_range.start.line == 2);
            assert!(info.position_range.start.column == 0);
            assert!(info.position_range.end.line == 2);
            assert!(info.position_range.end.column == 0);
            assert!(info.line_range.start == 1);
            assert!(info.line_range.end == 1);
        }
    }

    #[test]
    fn nl_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let result = lexer.next();
            let info = result.unwrap();
            assert!(info.kind == TokenKind::Nl);
            assert!(info.string_range.start == 0);
            assert!(info.string_range.end == 1);
            assert!(info.position_range.start.line == 1);
            assert!(info.position_range.start.column == 0);
            assert!(info.position_range.end.line == 1);
            assert!(info.position_range.end.column == 1);
            assert!(info.line_range.start == 0);
            assert!(info.line_range.end == 1);
        }
        {
            let result = lexer.next();
            let info = result.unwrap();
            assert!(info.kind == TokenKind::Endmarker);
            assert!(info.string_range.start == 1);
            assert!(info.string_range.end == 1);
            assert!(info.position_range.start.line == 2);
            assert!(info.position_range.start.column == 0);
            assert!(info.position_range.end.line == 2);
            assert!(info.position_range.end.column == 0);
            assert!(info.line_range.start == 1);
            assert!(info.line_range.end == 1);
        }
    }

    #[test]
    fn nl_carriage_return_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let result = lexer.next();
            let info = result.unwrap();
            assert!(info.kind == TokenKind::Nl);
            assert!(info.string_range.start == 0);
            assert!(info.string_range.end == 1);
            assert!(info.position_range.start.line == 1);
            assert!(info.position_range.start.column == 0);
            assert!(info.position_range.end.line == 1);
            assert!(info.position_range.end.column == 1);
            assert!(info.line_range.start == 0);
            assert!(info.line_range.end == 1);
        }
        {
            let result = lexer.next();
            let info = result.unwrap();
            assert!(info.kind == TokenKind::Endmarker);
            assert!(info.string_range.start == 1);
            assert!(info.string_range.end == 1);
            assert!(info.position_range.start.line == 2);
            assert!(info.position_range.start.column == 0);
            assert!(info.position_range.end.line == 2);
            assert!(info.position_range.end.column == 0);
            assert!(info.line_range.start == 1);
            assert!(info.line_range.end == 1);
        }
    }
}
