use crate::{
    core::{ByteRange, KeywordMap, Position, PositionRange, Token, TokenInfoPtr, TokenKind},
    lookaround_buf_reader::LookaroundBufReader,
};
use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read};

pub(crate) struct LineScanner<'a, R> {
    keyword_map: &'a KeywordMap,
    reader: &'a mut LookaroundBufReader<R>,
    line_start: usize,
    line: usize,
    column: usize,
    tokens: Vec<Token>,
}

impl<'a, R> LineScanner<'a, R>
where
    R: Read,
{
    pub(crate) fn new(
        keyword_map: &'a KeywordMap,
        reader: &'a mut LookaroundBufReader<R>,
        line: usize,
    ) -> Self {
        let line_start = reader.absolute_offset();
        return Self {
            keyword_map,
            reader,
            line_start,
            line,
            column: 0,
            tokens: vec![],
        };
    }

    pub(crate) fn scan(&mut self, token_info_queue: &mut VecDeque<TokenInfoPtr>) -> Result<()> {
        loop {
            let Some(byte) = self.reader.read(0)? else {
                self.handle_eof()?;
                break;
            };
            match byte {
                b'\r' | b'\n' => {
                    self.handle_line_separator()?;
                    break;
                }
                _ => {
                    bail!("Unexpected byte pattern. byte: {}", byte);
                }
            }
        }
        // tokens to token_info_queue
        let line_end = 
        let line_range = ByteRange {
            start: self.line_start,
            end: self.reader.absolute_offset();
        }
        token_info_queue.reserve(self.tokens.len());
        token_info_queue.extend(tokens.into_iter().map(|t| {
            TokenInfo {
                token,
                line_range
            }
        }));
        Ok(())
    }

    fn handle_eof(&mut self) -> Result<()> {
        debug_assert!(self.reader.read(0)?.is_none());
        if !self.tokens.is_empty() {
            let has_line_separator = self
                .tokens
                .iter()
                .rev()
                .any(|t| t.kind == TokenKind::Nl || t.kind == TokenKind::Newline);
            if !has_line_separator {
                self.scan_string(|ctx| {
                    ctx.column += 1;
                    // TODO(harry): change token kind logic with condition
                    Ok(TokenKind::Nl)
                })?;
            }
        }
        todo!();
    }

    fn handle_line_separator(&mut self) -> Result<()> {
        todo!();
    }

    fn scan_string<F>(&mut self, string_scanner: F) -> Result<()>
    where
        F: FnOnce(&mut Self) -> Result<TokenKind>,
    {
        let string_start = self.reader.absolute_offset();
        let position_start = Position {
            line: self.line,
            column: self.column,
        };
        let kind = string_scanner(self)?;
        self.tokens.push(Token {
            kind,
            string_range: ByteRange {
                start: string_start,
                end: self.reader.absolute_offset(),
            },
            position_range: PositionRange {
                start: position_start,
                end: Position {
                    line: self.line,
                    column: self.column,
                },
            },
        });
        Ok(())
    }
}
