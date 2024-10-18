use crate::{
    core::{KeywordMap, TokenInfoPtr, TokenKind},
    line_scanner::LineScanner,
    lookaround_buf_reader::LookaroundBufReader,
};
use anyhow::{bail, Result};
use std::{collections::VecDeque, io::Read};

pub struct Lexer<'a, R> {
    keyword_map: &'a KeywordMap,
    reader: LookaroundBufReader<R>,
    token_info_queue: VecDeque<TokenInfoPtr>,
    line: usize,
    is_done: bool,
}

impl<'a, R> Lexer<'a, R>
where
    R: Read,
{
    pub fn new(keyword_map: &'a KeywordMap, reader: LookaroundBufReader<R>) -> Self {
        Self {
            keyword_map,
            reader,
            token_info_queue: VecDeque::new(),
            line: 1,
            is_done: false,
        }
    }

    pub fn next(&mut self) -> Result<TokenInfoPtr> {
        loop {
            if self.is_done {
                bail!("Endmarker has been processed");
            }

            if let Some(token_info) = self.token_info_queue.pop_front() {
                if token_info.token.kind == TokenKind::Endmarker {
                    self.is_done = true;
                }
                return Ok(token_info);
            }
            let mut scanner = LineScanner::new(self.keyword_map, &mut self.reader, self.line);
            scanner.scan(&mut self.token_info_queue)?;
        }
    }

    fn update(&mut self, scanner: LineScanner<'_, R>) -> Result<()> {
        todo!();
    }
}
