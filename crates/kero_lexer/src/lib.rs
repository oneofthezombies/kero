mod utils;

use std::io::{BufRead, BufReader, Read};

use kero_trie::Trie;
use utils::{is_carriage_return, is_line_feed, is_space, is_tab};

#[derive(Debug, PartialEq)]
enum TokenKind {
    Eof,

    Identifier,
    NumberLiteral,
    SingleLineStringLiteral,
    MultiLineStringLiteral,

    // Keywords
    As,     // as
    From,   // from
    Import, // import
    True,   // True
    False,  // False
    None,   // None

    // Symbols
    Asterisk,   // *
    Colon,      // :
    Equal,      // =
    LeftParen,  // (
    RightParen, // )
    Indent,     // Indent 4 spaces beyond the line above.
    Dedent,     // Dedent 4 spaces beyond the line above.
    Minus,      // -
    Plus,       // +
}

#[derive(Debug)]
struct Token {
    kind: TokenKind,
    start: Option<Position>, // inclusive
    end: Option<Position>,   // exclusive
}

#[derive(Debug)]
enum LexerError {
    Io(std::io::Error),
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
    R: std::io::Read,
{
    keywords: &'a Trie<u8>,
    reader: BufReader<R>,
    pos: Position,
    indent_stack: Vec<usize>,
}

impl<'a, R> Lexer<'a, R>
where
    R: std::io::Read,
{
    pub fn new(keywords: &'a Trie<u8>, reader: std::io::BufReader<R>) -> Lexer<'a, R> {
        Lexer {
            keywords,
            reader,
            pos: Position::new(),
            indent_stack: vec![0],
        }
    }

    pub fn next(&mut self) -> Result<Token, LexerError> {
        let mut buffer = [0u8, 1];
        let count = self
            .reader
            .read(&mut buffer)
            .map_err(|e| LexerError::Io(e))?;
        if count == 0 {
            return Ok(Token {
                kind: TokenKind::Eof,
                start: None,
                end: None,
            });
        }
        Ok(Token {
            kind: TokenKind::Eof,
            start: None,
            end: None,
        })
    }
}

#[cfg(test)]
mod tests {
    use kero_trie::TrieBuilder;

    use super::*;

    #[test]
    fn test_lexer() {
        let text = r#""#;
        let reader = BufReader::new(text.as_bytes());
        let trie = TrieBuilder::<u8>::new().build();
        let mut lexer = Lexer::new(&trie, reader);
        let result = lexer.next();
        let a = result.unwrap();
        assert_eq!(a.kind, TokenKind::Eof);
    }
}
