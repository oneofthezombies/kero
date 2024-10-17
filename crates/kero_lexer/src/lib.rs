mod core;
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

#[cfg(test)]
mod tests {
    use super::*;
    use crate::core::TokenKind;
    use kero_trie::TrieBuilder;

    struct CheckInfo<'a> {
        source: &'a [u8],
        info: &'a TokenInfoPtr,
        kind: TokenKind,
        string_range: (usize, usize),
        string: &'a [u8],
        position_range: ((usize, usize), (usize, usize)),
        line_range: (usize, usize),
        line: &'a [u8],
    }

    fn check_info(check_info: CheckInfo) {
        assert_eq!(
            check_info.info.kind, check_info.kind,
            "kind real: {:?} expected: {:?}",
            check_info.info.kind, check_info.kind
        );
        assert_eq!(
            check_info.info.string_range.start, check_info.string_range.0,
            "string_range.start real: {} expected: {}",
            check_info.info.string_range.start, check_info.string_range.0,
        );
        assert_eq!(
            check_info.info.string_range.end, check_info.string_range.1,
            "string_range.end real: {} expected: {}",
            check_info.info.string_range.end, check_info.string_range.1,
        );
        assert_eq!(
            &check_info.source[check_info.string_range.0..check_info.string_range.1],
            check_info.string,
            "string real: {:?} expected: {:?}",
            &check_info.source[check_info.string_range.0..check_info.string_range.1],
            check_info.string,
        );
        assert_eq!(
            check_info.info.position_range.start.line, check_info.position_range.0 .0,
            "position_range.start.line real: {} expected: {}",
            check_info.info.position_range.start.line, check_info.position_range.0 .0,
        );
        assert_eq!(
            check_info.info.position_range.start.column, check_info.position_range.0 .1,
            "position_range.start.column real: {} expected: {}",
            check_info.info.position_range.start.column, check_info.position_range.0 .1,
        );
        assert_eq!(
            check_info.info.position_range.end.line, check_info.position_range.1 .0,
            "position_range.end.line real: {} expected: {}",
            check_info.info.position_range.end.line, check_info.position_range.1 .0,
        );
        assert_eq!(
            check_info.info.position_range.end.column, check_info.position_range.1 .1,
            "position_range.end.line real: {} expected: {}",
            check_info.info.position_range.end.column, check_info.position_range.1 .1,
        );
        assert_eq!(
            check_info.info.line_range.start, check_info.line_range.0,
            "line_range.start real: {} expected: {}",
            check_info.info.line_range.start, check_info.line_range.0,
        );
        assert_eq!(
            check_info.info.line_range.end, check_info.line_range.1,
            "line_range.end real: {} expected: {}",
            check_info.info.line_range.end, check_info.line_range.1,
        );
        assert_eq!(
            &check_info.source[check_info.line_range.0..check_info.line_range.1],
            check_info.line,
            "line real: {:?} expected: {:?}",
            &check_info.source[check_info.line_range.0..check_info.line_range.1],
            check_info.line,
        );
    }

    #[test]
    fn endmarker() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Endmarker,
            string_range: (0, 0),
            string: b"",
            position_range: ((1, 0), (1, 0)),
            line_range: (0, 0),
            line: b"",
        });
    }

    #[test]
    fn nl_carriage_return() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\r";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (0, 1),
                string: b"\r",
                position_range: ((1, 0), (1, 1)),
                line_range: (0, 1),
                line: b"\r",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Endmarker,
                string_range: (1, 1),
                string: b"",
                position_range: ((2, 0), (2, 0)),
                line_range: (1, 1),
                line: b"",
            });
        }
    }

    #[test]
    fn nl_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (0, 1),
                string: b"\n",
                position_range: ((1, 0), (1, 1)),
                line_range: (0, 1),
                line: b"\n",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Endmarker,
                string_range: (1, 1),
                string: b"",
                position_range: ((2, 0), (2, 0)),
                line_range: (1, 1),
                line: b"",
            });
        }
    }

    #[test]
    fn nl_carriage_return_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"\r\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (0, 2),
                string: b"\r\n",
                position_range: ((1, 0), (1, 2)),
                line_range: (0, 2),
                line: b"\r\n",
            });
        }
    }

    #[test]
    fn comment() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"#";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Comment,
                string_range: (0, 1),
                string: b"#",
                position_range: ((1, 0), (1, 1)),
                line_range: (0, 1),
                line: b"#",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (1, 1),
                string: b"",
                position_range: ((1, 1), (1, 2)),
                line_range: (0, 1),
                line: b"#",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Endmarker,
                string_range: (1, 1),
                string: b"",
                position_range: ((2, 0), (2, 0)),
                line_range: (1, 1),
                line: b"",
            });
        }
    }

    #[test]
    fn comment_carriage_return() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"#\r";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Comment,
                string_range: (0, 1),
                string: b"#",
                position_range: ((1, 0), (1, 1)),
                line_range: (0, 2),
                line: b"#\r",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (1, 2),
                string: b"\r",
                position_range: ((1, 1), (1, 2)),
                line_range: (0, 2),
                line: b"#\r",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Endmarker,
                string_range: (2, 2),
                string: b"",
                position_range: ((2, 0), (2, 0)),
                line_range: (2, 2),
                line: b"",
            });
        }
    }

    #[test]
    fn comment_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"#\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Comment,
                string_range: (0, 1),
                string: b"#",
                position_range: ((1, 0), (1, 1)),
                line_range: (0, 2),
                line: b"#\n",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (1, 2),
                string: b"\n",
                position_range: ((1, 1), (1, 2)),
                line_range: (0, 2),
                line: b"#\n",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Endmarker,
                string_range: (2, 2),
                string: b"",
                position_range: ((2, 0), (2, 0)),
                line_range: (2, 2),
                line: b"",
            });
        }
    }

    #[test]
    fn comment_carriage_return_line_feed() {
        let builder = TrieBuilder::<u8>::new();
        let keywords = builder.build();
        let source = b"#\r\n";
        let mut lexer = Lexer::new(&keywords, source.as_slice());
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Comment,
                string_range: (0, 1),
                string: b"#",
                position_range: ((1, 0), (1, 1)),
                line_range: (0, 3),
                line: b"#\r\n",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Nl,
                string_range: (1, 3),
                string: b"\r\n",
                position_range: ((1, 1), (1, 3)),
                line_range: (0, 3),
                line: b"#\r\n",
            });
        }
        {
            let info = lexer.next().unwrap();
            check_info(CheckInfo {
                source,
                info: &info,
                kind: TokenKind::Endmarker,
                string_range: (3, 3),
                string: b"",
                position_range: ((2, 0), (2, 0)),
                line_range: (3, 3),
                line: b"",
            });
        }
    }
}
