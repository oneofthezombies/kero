use crate::{
    core::{ByteRange, KeywordMap, Position, PositionRange, Token, TokenInfo, TokenKind},
    lookaround_buf_reader::LookaroundBufReader,
    utf8::unchecked::ByteKind,
};
use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read, str};
use unicode_ident::is_xid_continue;

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
                b'#' => self.handle_sharp(byte)?,
                x if is_line_separator(x) => {
                    self.handle_line_separator(byte)?;
                    break;
                }
                x if is_ascii_xid_start(x) => self.handle_ascii_xid_start(byte)?,
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
                self.scan_string_and_increase_line(|this| {
                    this.column += 1;
                    // TODO(harry): change token kind logic with condition
                    Ok(TokenKind::Nl)
                })?;
                return Ok(());
            }
        }
        self.scan_string(|_| {
            return Ok(TokenKind::Endmarker);
        })
    }

    fn handle_line_separator(&mut self, byte: u8) -> Result<()> {
        debug_assert!(is_line_separator(byte));
        self.scan_string_and_increase_line(|this| {
            this.advance_and_increase_column(1)?;
            if byte == b'\r' {
                if let Some(next) = this.lexer.reader.read(0)? {
                    if next == b'\n' {
                        this.advance_and_increase_column(1)?;
                    }
                }
            }
            // TODO(harry): change token kind logic with condition
            Ok(TokenKind::Nl)
        })
    }

    fn handle_sharp(&mut self, byte: u8) -> Result<()> {
        debug_assert!(byte == b'#');
        self.scan_string(|this| {
            this.advance_and_increase_column(1)?;
            loop {
                let Some(byte) = this.lexer.reader.read(0)? else {
                    break;
                };
                if is_line_separator(byte) {
                    break;
                }
                this.advance_and_increase_column(1)?
            }
            Ok(TokenKind::Comment)
        })
    }

    fn handle_ascii_xid_start(&mut self, byte: u8) -> Result<()> {
        debug_assert!(is_ascii_xid_start(byte));
        self.scan_string(|this| {
            this.advance_and_increase_column(1)?;
            loop {
                let Some(byte) = this.lexer.reader.read(0)? else {
                    break;
                };
                let kind = ByteKind::byte_kind(byte);
                let Some(trailing_byte_count) = kind.trailing_byte_count() else {
                    bail!("Unexpected start byte of UTF-8. byte: {}", byte);
                };
                if trailing_byte_count == 0 {
                    if !is_ascii_xid_continue(byte) {
                        break;
                    }
                } else {
                    let mut buf = [0u8; 4];
                    buf[0] = byte;
                    debug_assert!(trailing_byte_count <= 3);
                    for i in 1..=trailing_byte_count {
                        let Some(trailing) = this.lexer.reader.read(i.try_into()?)? else {
                            bail!("Unexpected EOF encountered instead of UTF-8 continuation.");
                        };
                        buf[i] = trailing;
                    }
                    let str = str::from_utf8(&buf[0..=trailing_byte_count])?;
                    let Some(ch) = str.chars().next() else {
                        bail!("Must exist character present");
                    };
                    if !is_xid_continue(ch) {
                        break;
                    }
                }
                this.advance_and_increase_column(1 + trailing_byte_count)?;
            }
            Ok(TokenKind::Name)
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
        self.column = 0;
        Ok(())
    }

    fn advance_and_increase_column(&mut self, offset: usize) -> Result<()> {
        self.lexer.reader.advance(offset.try_into()?)?;
        self.column += offset;
        Ok(())
    }
}

fn is_line_separator(byte: u8) -> bool {
    byte == b'\r' || byte == b'\n'
}

fn is_ascii_xid_start(byte: u8) -> bool {
    match byte {
        b'A'..=b'Z' | b'a'..=b'z' | b'_' => true,
        _ => false,
    }
}

fn is_ascii_xid_continue(byte: u8) -> bool {
    match byte {
        b'0'..=b'9' => true,
        x if is_ascii_xid_start(x) => true,
        _ => false,
    }
}
