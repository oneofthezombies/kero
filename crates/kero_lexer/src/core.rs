use kero_trie::{Trie, TrieBuilder};

#[derive(Clone, Debug, PartialEq)]
pub enum TokenKind {
    Endmarker, // EOF
    Newline,
    Nl,
    Indent,
    Dedent,
    Comment, // #
}

#[derive(Clone, Debug)]
pub struct ByteRange {
    pub start: usize, // inclusive
    pub end: usize,   // exclusive
}

#[derive(Clone, Debug, PartialEq)]
pub struct Position {
    pub line: usize,
    pub column: usize,
}

impl Position {
    pub(crate) fn new() -> Self {
        Self { line: 1, column: 0 }
    }
}

#[derive(Debug)]
pub struct PositionRange {
    pub start: Position, // inclusive
    pub end: Position,   // exclusive
}

#[derive(Debug)]
pub struct Token {
    pub kind: TokenKind,
    pub string_range: ByteRange,
    pub position_range: PositionRange,
}

#[derive(Debug)]
pub struct TokenInfo {
    pub token: Token,
    pub line_range: ByteRange,
}

pub type KeywordMap = Trie<u8>;
pub type KeywordMapBuilder = TrieBuilder<u8>;
