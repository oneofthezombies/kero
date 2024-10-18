mod core;
mod lexer;
mod line_scanner;
mod lookaround_buf_reader;
mod string_scanner;
mod utf8;

use crate::{
    core::TokenInfoPtr, line_scanner::LineScanner, lookaround_buf_reader::LookaroundBufReader,
};
use anyhow::{bail, Result};
use core::Scanner;
use kero_trie::Trie;
use std::{collections::VecDeque, io::Read};
use unicode_ident::is_xid_start;

pub(crate) struct LexerContext<'ke, R> {
    pub(crate) keywords: &'ke Trie<u8>,
    pub(crate) reader: LookaroundBufReader<R>,
    pub(crate) info_queue: VecDeque<TokenInfoPtr>,
    pub(crate) indent_stack: Vec<usize>,
    pub(crate) bracket_level: usize,
    pub(crate) line: usize,
    pub(crate) is_processed_endmarker: bool,
}

struct Lexer<'ke, R> {
    ctx: LexerContext<'ke, R>,
}

impl<'ke, R> Lexer<'ke, R>
where
    R: Read,
{
    pub fn new(keywords: &'ke Trie<u8>, reader: R) -> Lexer<'ke, R> {
        Lexer {
            ctx: LexerContext {
                keywords,
                reader: LookaroundBufReader::with_lookbehind_capacity(reader, 1),
                indent_stack: vec![0],
                bracket_level: 0,
                line: 1,
                info_queue: VecDeque::<TokenInfoPtr>::new(),
                is_processed_endmarker: false,
            },
        }
    }

    pub fn next(&mut self) -> Result<TokenInfoPtr> {
        loop {
            // if let Some(info) = self.info_queue.pop_front() {
            //     return Ok(info);
            // }

            // if self.is_processed_endmarker {
            //     bail!("All tokens have already been processed");
            // }

            LineScanner::new(&mut self.ctx).scan()?;
        }
    }

    // fn advance(&mut self, line_ctx: &mut LineContext, offset: usize) -> Result<()> {
    //     self.reader.advance(offset.try_into()?)?;
    //     line_ctx.column += offset;
    //     Ok(())
    // }
}
