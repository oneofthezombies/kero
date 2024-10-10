mod utils;

use core;
use kero_trie::Trie;
use std::str::{Bytes, CharIndices};
use utils::{
    is_alpha_lower, is_alpha_upper, is_carriage_return, is_line_feed, is_underscore, is_whitespace,
};

#[derive(PartialEq)]
enum TokenKind {
    Eof,
    NewLine,
    Identifier,

    // Keywords
    As,     // as
    From,   // from
    Import, // import

    // Symbols
    Asterisk,   // *
    Colon,      // :
    Equal,      // =
    LeftParen,  // (
    RightParen, // )
}

struct Token {
    kind: TokenKind,
    start: usize, // inclusive
    end: usize,   // exclusive
}

#[derive(Debug)]
enum LexerError {
    PreviousCursorAlreadyExist,
    BytesIsEmpty,
    CharIndicesIsEmpty,
}

// impl core::error::Error for NextError {}

// impl core::fmt::Display for NextError {
//     fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
//         // match self {
//         //     NextError::UnexpectedChar(c) => write!(f, "Unexpected character: '{}'", c),
//         // }
//     }
// }

#[derive(Clone)]
struct Cursor {
    byte_i: usize,
    line: usize,
    column: usize,
}

struct Lexer<'a> {
    keywords: &'a Trie<u8>,
    source: &'a str,
    previous: Option<Cursor>,
    current: Option<Cursor>,
    token: Option<Token>,
}

impl<'a> Lexer<'a> {
    pub fn new(keywords: &'a Trie<u8>, source: &'a str) -> Lexer<'a> {
        Lexer {
            keywords,
            source,
            bytes: source.bytes(),
            char_indices: source.char_indices(),
            previous: None,
            current: None,
            token: None,
        }
    }

    fn consume(&mut self) -> Result<(), LexerError> {
        let Some(current) = self.current.as_ref() else {
            if self.previous.is_some() {
                return Err(LexerError::PreviousCursorAlreadyExist);
            }

            let Some(byte) = self.bytes.next() else {
                return Err(LexerError::BytesIsEmpty);
            };

            let Some((char_byte_i, char)) = self.char_indices.next() else {
                return Err(LexerError::CharIndicesIsEmpty);
            };

            let line_factor: usize = if is_carriage_return(byte) || is_line_feed(byte) {
                1
            } else {
                0
            };

            self.current = Some(Cursor {
                byte,
                byte_i: 0,
                char,
                char_i: 0,
                char_byte_i,
                line: line_factor,
                column: 1,
            });
            return Ok(());
        };

        self.previous = Some(current.clone());

        let Some(byte) = self.bytes.next() else {
            return Err(LexerError::BytesIsEmpty);
        };

        let Some((char_byte_i, char)) = self.char_indices.next() else {
            return Err(LexerError::CharIndicesIsEmpty);
        };

        let line_factor: usize = if is_carriage_return(byte) || is_line_feed(byte) {
            1
        } else {
            0
        };

        return Ok(());
    }

    pub fn next(&mut self) -> Result<(), LexerError> {
        Ok(())
    }

    pub fn current(&self) -> Option<&Token> {
        self.token.as_ref()
    }

    // fn traverse(&mut self) {
    //     if self.match_eof()? {
    //         Ok(())
    //     }

    //     if self.match_newline()? {
    //         Ok(())
    //     }

    //     if self.match_whitespace()? {
    //         Ok(())
    //     }

    //     if self.match_comment()? {
    //         Ok(())
    //     }

    //     if self.match_symbol()? {
    //         Ok(())
    //     }

    //     if self.match_keyword_or_identifier()? {
    //         Ok(())
    //     }
    // }

    // fn match_eof(&mut self) -> Result<(), LexerError> {
    //     self.consume_right();
    // }

    // fn match_whitespace(&mut self) {
    //     if self.match_space()? {
    //         Ok(())
    //     }

    //     if self.match_tab()? {
    //         Ok(())
    //     }
    // }

    // fn match_comment(&mut self) {
    //     if self.match_multiline_comment()? {
    //         Ok(())
    //     }

    //     if self.match_singleline_comment()? {
    //         Ok(())
    //     }
    // }

    fn consume_right(&mut self) -> bool {
        return false;
    }

    fn consume_left(&mut self) {}
}

#[cfg(test)]
mod tests {
    use kero_trie::TrieBuilder;

    use super::*;

    #[test]
    fn test_import_a() {
        let file_content = r#"import a"#;
        // let mut lexer = Lexer::new(file_content);
        // let token = lexer.token();
        // lexer.eat();
    }

    #[test]
    fn test_index() {
        let source = "Hello, 世界";
        println!("source: {} ", source);
        println!("source len: {}", source.len());
        let keywords = TrieBuilder::<u8>::new().build();
        let mut lexer = Lexer::new(&keywords, source);
        {
            let result = lexer.consume();
            assert!(result.is_ok());
            assert!(lexer.current.is_some());
            let current = lexer.current.as_ref().unwrap();
            println!("byte: {}", current.byte);
            println!("byte_i: {}", current.byte_i);
            println!("char: {}", current.char);
            println!("char_i: {}", current.char_i);
            println!("char_byte_i: {}", current.char_byte_i);
            println!("line: {}", current.line);
            println!("column: {}", current.column);
        }
        {
            let result = lexer.consume();
            assert!(result.is_ok());
            assert!(lexer.current.is_some());
            let current = lexer.current.as_ref().unwrap();
            println!("byte: {}", current.byte);
            println!("byte_i: {}", current.byte_i);
            println!("char: {}", current.char);
            println!("char_i: {}", current.char_i);
            println!("char_byte_i: {}", current.char_byte_i);
            println!("line: {}", current.line);
            println!("column: {}", current.column);
        }
    }
}
