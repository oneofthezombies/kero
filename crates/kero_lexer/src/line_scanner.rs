use crate::{
    core::{Position, Scanner, TokenInfoPtr, TokenKind},
    lookaround_buf_reader::LookaroundBufReader,
    string_scanner::{AutoNlStringScanner, EndmarkerStringScanner, NlStringScanner, StringScanner},
    Lexer, LexerContext,
};
use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read};

pub(crate) struct LineScannerContext<'le, 'ke, R> {
    pub(crate) ctx: &'le mut LexerContext<'ke, R>,
    pub(crate) line_start: usize,
    pub(crate) info_start_index: usize,
    pub(crate) column: usize,
    pub(crate) is_processed_nl_or_newline: bool,
    pub(crate) is_processed_name_or_string: bool,
}

pub(crate) struct LineScanner<'le, 'ke, R> {
    ctx: LineScannerContext<'le, 'ke, R>,
}

impl<'le, 'ke, R> LineScanner<'le, 'ke, R>
where
    R: Read,
{
    pub(crate) fn new(ctx: &'le mut LexerContext<'ke, R>) -> Self {
        let line_start = ctx.reader.total_offset();
        let info_start_index = ctx.info_queue.len();
        return Self {
            ctx: LineScannerContext {
                ctx,
                line_start,
                info_start_index,
                column: 0,
                is_processed_nl_or_newline: false,
                is_processed_name_or_string: false,
            },
        };
    }

    fn on_eof(&mut self) -> Result<()> {
        debug_assert!(self.ctx.ctx.reader.read(0)?.is_none());

        if self.ctx.info_start_index < self.ctx.ctx.info_queue.len() {
            if !self.ctx.is_processed_nl_or_newline {
                let is_processed_name_or_string = self.ctx.is_processed_name_or_string;
                AutoNlStringScanner {
                    inner: NlStringScanner {
                        inner: StringScanner::new(&mut self.ctx),
                        kind: if is_processed_name_or_string {
                            TokenKind::Nl
                        } else {
                            TokenKind::Newline
                        },
                    },
                }
                .scan()?;
            }
        }

        EndmarkerStringScanner {
            inner: StringScanner::new(&mut self.ctx),
        }
        .scan()?;
        Ok(())
    }

    // fn on_carriage_return_or_line_feed(&mut self, byte: u8) -> Result<()> {
    //     debug_assert!(byte == b'\r' || byte == b'\n');

    //     let str_ctx = self.create_string_context(line_ctx);
    //     let Some(current) = self.reader.read(0)? else {
    //         bail!("Must have a byte present");
    //     };

    //     self.advance(line_ctx, 1)?;

    //     if current == b'\r' {
    //         if let Some(next) = self.reader.read(0)? {
    //             if next == b'\n' {
    //                 self.advance(line_ctx, 1)?;
    //             }
    //         }
    //     }

    //     self.push_info_nl_or_newline(
    //         line_ctx,
    //         &str_ctx,
    //         if line_ctx.is_processed_name_or_string {
    //             TokenKind::Newline
    //         } else {
    //             TokenKind::Nl
    //         },
    //     );
    //     Ok(())
    // }

    // fn on_sharp(&mut self, byte: u8) -> Result<()> {
    //     debug_assert!(byte == b'#');

    //     let str_ctx = self.create_string_context(line_ctx);
    //     self.advance(line_ctx, 1)?;

    //     loop {
    //         if self.is_eof()? {
    //             break;
    //         }

    //         if self.is_line_separator()? {
    //             break;
    //         }

    //         self.advance(line_ctx, 1)?;
    //     }

    //     self.push_info(&line_ctx, &str_ctx, TokenKind::Comment);
    //     Ok(())
    // }

    fn update_line_end(&mut self) -> Result<()> {
        for i in self.ctx.info_start_index..self.ctx.ctx.info_queue.len() {
            let Some(info) = self.ctx.ctx.info_queue.get_mut(i) else {
                bail!("Must have a info present");
            };

            info.line_range.end = self.ctx.ctx.reader.total_offset();
        }
        Ok(())
    }
}

impl<'l, 'k, R> Scanner for LineScanner<'l, 'k, R>
where
    R: Read,
{
    fn scan(&mut self) -> Result<()> {
        loop {
            let Some(byte) = self.ctx.ctx.reader.read(0)? else {
                self.on_eof()?;
                break;
            };
            match byte {
                // b'\r' | b'\n' => {
                //     self.on_carriage_return_or_line_feed(byte)?;
                //     break;
                // }
                // b'#' => {
                //     self.on_sharp(byte)?;
                // }
                _ => {
                    bail!("Unexpected pattern");
                }
            }
        }
        self.update_line_end()?;
        Ok(())
    }
}
