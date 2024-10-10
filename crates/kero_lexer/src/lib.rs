use crate::trie;
use core;

enum TokenKind {
    Eof,
    NewLine,
    Identifier,

    // Keywords
    Import, // import
    From,   // from
    As,     // as

    // Symbols
    Asterisk, // *
}

struct Token {
    kind: TokenKind,
    start: usize, // inclusive
    end: usize,   // exclusive
}

#[derive(Debug)]
enum NextError {
    PositionOutOfRange(usize),
    UnexpectedChar(char),
}

impl core::error::Error for NextError {}

impl core::fmt::Display for NextError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            NextError::UnexpectedChar(c) => write!(f, "Unexpected character: '{}'", c),
        }
    }
}

struct Lexer<'a> {
    source: &'a str,
    position: usize,
    current: Option<Token>,
}

impl<'a> Lexer<'a> {
    fn new(source: &'_ str) -> Lexer {
        Lexer {
            source,
            position: 0,
            current: None,
        }
    }

    fn next(&mut self) -> Result<(), NextError> {
        let source_len = self.source.len();
        if self.position > source_len {
            Err(NextError::PositionOutOfRange(self.position))
        } else if self.position == source_len {
            self.current = Some(Token {
                kind: TokenKind::Eof,
                start: self.position,
                end: self.position,
            });

            // When next is called, NextError::PositionOutOfRange is returned to prevent duplicate calls to TokenKind::Eof.
            self.position = source_len + 1;
            Ok(())
        } else {
            let start = self.position;
            let mut end = self.position;
            while end < source_len {}
            self.position = end;
            Ok(())
        }
    }

    fn current(&mut self) {}
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_import_a() {
        let file_content = r#"import a"#;
        // let mut lexer = Lexer::new(file_content);
        // let token = lexer.token();
        // lexer.eat();
    }
}
