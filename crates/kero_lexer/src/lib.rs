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
    infos: Vec<TokenInfoPtr>,
    line_start_offset: usize,
    column: usize,
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
        let mut ctx = self.on_start_parse_line();
        loop {
            if self.is_start_of_endmarker()? {
                self.process_endmarker(&mut ctx)?;
                break;
            } else if self.is_start_of_nl_or_newline()? {
                self.process_nl_or_newline(&mut ctx)?;
                break;
            } else {
                todo!();
            }
        }
        self.on_complete_parse_line(ctx);
        Ok(())
    }

    fn on_start_parse_line(&self) -> LineContext {
        return LineContext {
            infos: vec![],
            line_start_offset: self.reader.get_total_offset(),
            column: 0,
        };
    }

    fn on_complete_parse_line(&mut self, mut ctx: LineContext) {
        for info in &mut ctx.infos {
            info.line_range.end = self.reader.get_total_offset();
        }
        self.info_queue.extend(ctx.infos.drain(..));
    }

    fn push_info(
        &self,
        ctx: &mut LineContext,
        kind: TokenKind,
        string_start: usize,
        position_start: Position,
    ) {
        ctx.infos.push(Box::new(TokenInfo {
            kind,
            string_range: ByteRange {
                start: string_start,
                end: self.reader.get_total_offset(),
            },
            position_range: PositionRange {
                start: position_start,
                end: Position {
                    line: self.line,
                    column: ctx.column,
                },
            },
            line_range: ByteRange {
                start: ctx.line_start_offset,
                end: 0, // set at on_complete_parse_line
            },
        }));
    }

    fn is_start_of_endmarker(&mut self) -> Result<bool> {
        let Some(_) = self.reader.read(0)? else {
            return Ok(true);
        };

        Ok(false)
    }

    fn process_endmarker(&mut self, ctx: &mut LineContext) -> Result<()> {
        debug_assert!(self.is_start_of_endmarker()?);

        if let Some(last) = ctx.infos.last() {
            let is_line_end_token = last.kind == TokenKind::Nl || last.kind == TokenKind::Newline;
            if !is_line_end_token {
                ctx.column += 1;
                self.push_info(
                    ctx,
                    TokenKind::Nl,
                    last.string_range.end,
                    last.position_range.end.clone(),
                );
                self.line += 1;
            }
        }

        self.push_info(
            ctx,
            TokenKind::Endmarker,
            self.reader.get_total_offset(),
            Position {
                line: self.line,
                column: ctx.column,
            },
        );

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

    fn process_nl_or_newline(&mut self, ctx: &mut LineContext) -> Result<()> {
        debug_assert!(self.is_start_of_nl_or_newline()?);

        let Some(current) = self.reader.read(0)? else {
            bail!("Must have a byte present");
        };

        let string_start = self.reader.get_total_offset();
        let position_start = self.position.clone();

        self.position.line += 1;
        self.position.column = 0;
        self.reader.advance(1)?;

        if current == b'\r' {
            if let Some(next) = self.reader.read(1)? {
                if next == b'\n' {
                    self.reader.advance(1)?;
                }
            }
        }

        //     self.push_info(
        //         if self.paren_count > 0 {
        //             TokenKind::Nl
        //         } else {
        //             TokenKind::Newline
        //         },
        //         string_start,
        //         position_start,
        //     );
        //     Ok(())
        todo!();
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
