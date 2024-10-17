use crate::{
    core::{ByteRange, Position, PositionRange, Scanner, TokenInfo, TokenInfoPtr, TokenKind},
    line_scanner::{LineScanner, LineScannerContext},
    lookaround_buf_reader::LookaroundBufReader,
};
use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read};

pub(crate) struct StringScannerContext<'ls, 'le, 'ke, R> {
    ctx: &'ls mut LineScannerContext<'le, 'ke, R>,
    string_start: usize,
    position_start: Position,
}

pub(crate) struct StringScanner<'ls, 'le, 'ke, R> {
    ctx: StringScannerContext<'ls, 'le, 'ke, R>,
}

impl<'ls, 'le: 'ls, 'ke: 'le, R> StringScanner<'ls, 'le, 'ke, R>
where
    R: Read,
{
    pub(crate) fn new(ctx: &'ls mut LineScannerContext<'le, 'ke, R>) -> Self {
        let string_start = ctx.ctx.reader.total_offset();
        let position_start = Position {
            line: ctx.ctx.line,
            column: ctx.column,
        };
        return Self {
            ctx: StringScannerContext {
                ctx,
                string_start,
                position_start,
            },
        };
    }

    fn commit(&mut self, kind: TokenKind) {
        self.ctx.ctx.ctx.info_queue.push_back(Box::new(TokenInfo {
            kind,
            string_range: ByteRange {
                start: self.ctx.string_start,
                end: self.ctx.ctx.ctx.reader.total_offset(),
            },
            position_range: PositionRange {
                start: self.ctx.position_start.clone(),
                end: Position {
                    line: self.ctx.ctx.ctx.line,
                    column: self.ctx.ctx.column,
                },
            },
            line_range: ByteRange {
                start: self.ctx.ctx.line_start,
                end: 0, // Set on update_line_range_end
            },
        }));
    }
}

pub(crate) struct NlStringScanner<'ls, 'l, 'k, R> {
    pub(crate) inner: StringScanner<'ls, 'l, 'k, R>,
    pub(crate) kind: TokenKind,
}

impl<'ls, 'l: 'ls, 'k: 'l, R> NlStringScanner<'ls, 'l, 'k, R>
where
    R: Read,
{
    pub(crate) fn commit(&mut self) -> Result<()> {
        if !(self.kind == TokenKind::Nl || self.kind == TokenKind::Newline) {
            bail!("Kind must be NL or NEWLINE");
        }
        self.inner.commit(self.kind.clone());
        self.inner.ctx.ctx.ctx.line += 1;
        self.inner.ctx.ctx.column = 0;
        Ok(())
    }
}

pub(crate) struct AutoNlStringScanner<'ls, 'l, 'k, R> {
    pub(crate) inner: NlStringScanner<'ls, 'l, 'k, R>,
}

impl<'ls, 'l: 'ls, 'k: 'l, R> Scanner for AutoNlStringScanner<'ls, 'l, 'k, R>
where
    R: Read,
{
    fn scan(&mut self) -> Result<()> {
        self.inner.inner.ctx.ctx.column += 1; // Treat it as being at the end of the line.
        self.inner.commit()?;
        Ok(())
    }
}

pub(crate) struct EndmarkerStringScanner<'ls, 'l, 'k, R> {
    pub(crate) inner: StringScanner<'ls, 'l, 'k, R>,
}

impl<'ls, 'l: 'ls, 'k: 'l, R> Scanner for EndmarkerStringScanner<'ls, 'l, 'k, R>
where
    R: Read,
{
    fn scan(&mut self) -> Result<()> {
        Ok(())
    }
}
