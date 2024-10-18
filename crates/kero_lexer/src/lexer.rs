use crate::{
    core::{ByteRange, KeywordMap, Position, PositionRange, Token, TokenInfo, TokenKind},
    lookaround_buf_reader::LookaroundBufReader,
};
use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read};

pub struct Lexer<'a, R> {
    keyword_map: &'a KeywordMap,
    reader: LookaroundBufReader<R>,
    token_info_queue: VecDeque<TokenInfo>,
    line: usize,
}

impl<'a, R> Lexer<'a, R>
where
    R: Read,
{
    pub fn new(keyword_map: &'a KeywordMap, reader: R) -> Self {
        Self {
            keyword_map,
            reader: LookaroundBufReader::new(reader),
            token_info_queue: VecDeque::new(),
            line: 1,
        }
    }

    pub fn next(&mut self) -> Result<TokenInfo> {
        loop {
            if let Some(token_info) = self.token_info_queue.pop_front() {
                return Ok(token_info);
            }

            self.scan_line()?;
        }
    }

    fn scan_line(&mut self) -> Result<()> {
        let line_start = self.reader.absolute_offset();
        let mut scanner = LineScanner {
            lexer: self,
            tokens: vec![],
            column: 0,
        };
        scanner.scan()?;
        let line_range = ByteRange {
            start: line_start,
            end: scanner.lexer.reader.absolute_offset(),
        };
        let token_info_it = scanner.tokens.into_iter().map(|token| TokenInfo {
            token,
            line_range: line_range.clone(),
        });
        scanner.lexer.token_info_queue.extend(token_info_it);
        Ok(())
    }
}

struct LineScanner<'b, 'a, R> {
    lexer: &'b mut Lexer<'a, R>,
    tokens: Vec<Token>,
    column: usize,
}

impl<'b, 'a, R> LineScanner<'b, 'a, R>
where
    R: Read,
{
    fn scan(&mut self) -> Result<()> {
        loop {
            let Some(byte) = self.lexer.reader.read(0)? else {
                self.handle_eof()?;
                break;
            };
            match byte {
                b'\r' | b'\n' => {
                    self.handle_line_separator(byte)?;
                    break;
                }
                _ => {
                    bail!("Unexpected byte pattern. byte: {}", byte);
                }
            }
        }
        Ok(())
    }

    fn handle_eof(&mut self) -> Result<()> {
        debug_assert!(self.lexer.reader.read(0)?.is_none());
        if !self.tokens.is_empty() {
            let has_line_separator = self
                .tokens
                .iter()
                .rev()
                .any(|t| t.kind == TokenKind::Nl || t.kind == TokenKind::Newline);
            if !has_line_separator {
                self.scan_string_and_increase_line(|scanner| {
                    scanner.column += 1;
                    // TODO(harry): change token kind logic with condition
                    Ok(TokenKind::Nl)
                })?;
            }
        }
        self.scan_string(|_| {
            return Ok(TokenKind::Endmarker);
        })
    }

    fn handle_line_separator(&mut self, byte: u8) -> Result<()> {
        debug_assert!(byte == b'\r' || byte == b'\n');
        self.scan_string_and_increase_line(|scanner| {
            scanner.advance_and_increase_column(1)?;
            if byte == b'\r' {
                if let Some(next) = scanner.lexer.reader.read(0)? {
                    if next == b'\n' {
                        scanner.advance_and_increase_column(1)?;
                    }
                }
            }
            // TODO(harry): change token kind logic with condition
            Ok(TokenKind::Nl)
        })
    }

    fn scan_string<F>(&mut self, string_scanner: F) -> Result<()>
    where
        F: FnOnce(&mut Self) -> Result<TokenKind>,
    {
        let string_start = self.lexer.reader.absolute_offset();
        let position_start = Position {
            line: self.lexer.line,
            column: self.column,
        };
        let kind = string_scanner(self)?;
        self.tokens.push(Token {
            kind,
            string_range: ByteRange {
                start: string_start,
                end: self.lexer.reader.absolute_offset(),
            },
            position_range: PositionRange {
                start: position_start,
                end: Position {
                    line: self.lexer.line,
                    column: self.column,
                },
            },
        });
        Ok(())
    }

    fn scan_string_and_increase_line<F>(&mut self, string_scanner: F) -> Result<()>
    where
        F: FnOnce(&mut Self) -> Result<TokenKind>,
    {
        self.scan_string(string_scanner)?;
        self.lexer.line += 1;
        Ok(())
    }

    fn advance_and_increase_column(&mut self, offset: usize) -> Result<()> {
        self.lexer.reader.advance(offset.try_into()?)?;
        self.column += 1;
        Ok(())
    }
}
