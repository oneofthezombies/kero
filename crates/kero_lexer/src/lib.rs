mod utf8;
mod utils;

use crate::utf8::Utf8CharWindowBufReader;
use anyhow::{anyhow, bail, Result};
use kero_trie::Trie;
use std::io::{BufRead, BufReader, Read};

#[derive(Debug, PartialEq)]
enum TokenKind {
    Eof,

    Identifier,
    Number,
    String,

    // Keywords
    As,     // as
    From,   // from
    Import, // import
    True,   // True
    False,  // False
    None,   // None

    // Symbols
    Asterisk, // *
    Colon,    // :
    Equal,    // =
    LParen,   // (
    RParen,   // )
    Indent,   // Indent 4 spaces beyond the line above.
    Dedent,   // Dedent 4 spaces beyond the line above.
    Minus,    // -
    Plus,     // +
}

#[derive(Debug)]
struct Token {
    kind: TokenKind,
    start: Option<Position>, // inclusive
    end: Option<Position>,   // exclusive
}

#[derive(Debug, Clone)]
struct Position {
    index: usize,
    line: usize,
    column: usize,
}

impl Position {
    fn new() -> Self {
        Self {
            index: 0,
            line: 1,
            column: 1,
        }
    }
}

struct Lexer<'a, R>
where
    R: Read,
{
    keywords: &'a Trie<char>,
    reader: Utf8CharWindowBufReader<R>,
    indents: Vec<usize>,
    pos: Position,
}

impl<'a, R> Lexer<'a, R>
where
    R: Read,
{
    pub fn new(keywords: &'a Trie<char>, reader: R) -> Lexer<'a, R> {
        Lexer {
            keywords,
            reader: Utf8CharWindowBufReader::new(reader),
            indents: vec![0],
            pos: Position::new(),
        }
    }

    pub fn next(&mut self) -> Result<Token> {
        let cur = self.reader.get(0)?;
        let is_cond_of_eof = cur.is_none();
        if is_cond_of_eof {
            return Ok(Token {
                kind: TokenKind::Eof,
                start: Some(self.pos.clone()),
                end: None,
            });
        }

        let ch = cur.ok_or_else(|| anyhow!("Must ch exist after checking EOF"))?;
        let is_cond_of_indent_like = self.pos.column == 1;
        if is_cond_of_indent_like {
            if ch != ' ' {}

            let current_indent = 0usize;

            let last_indent = self
                .indents
                .last()
                .ok_or_else(|| anyhow!("Last indent must be exist"))?
                .clone();
        }

        Ok(Token {
            kind: TokenKind::Eof,
            start: None,
            end: None,
        })
    }

    fn parse_indent(&self) -> Result<usize> {
        let ch = self
            .reader
            .get(0)?
            .ok_or_else(|| anyhow!("Must ch exist in parse_indent"))?;
        if ch != ' ' {
            self.consume();
            return Ok(0);
        }
    }

    fn consume(&mut self) -> Result<()> {
        let ch = self.reader.get(0)?;
        let ch = self
            .ch
            .ok_or_else(|| anyhow!("Must self.ch exit in consume"))?;
        if ch == '\r' {
            self.pos.line += 1;
            self.pos.column = 1;
            // if next is \n consume
        } else if ch == '\n' {
            self.pos.line += 1;
            self.pos.column = 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use kero_trie::TrieBuilder;

    use super::*;

    #[test]
    fn test_lexer() {
        let text = r#"123"#;
        let mut reader = BufReader::new(text.as_bytes());
        let trie = TrieBuilder::<char>::new().build();
        let mut lexer = Lexer::new(&trie, &mut reader);
        let result = lexer.next();
        let error = result.unwrap_err();
        println!("@ {}", error.backtrace());
    }
}
