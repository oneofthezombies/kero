use kero_trie::Trie;

#[derive(Clone, Debug, PartialEq)]
pub(crate) enum TokenKind {
    Endmarker, // EOF
    Newline,
    Nl,
    Indent,
    Dedent,
    Comment, // #
}

#[derive(Clone, Debug)]
pub(crate) struct ByteRange {
    pub(crate) start: usize, // inclusive
    pub(crate) end: usize,   // exclusive
}

#[derive(Clone, Debug, PartialEq)]
pub(crate) struct Position {
    pub(crate) line: usize,
    pub(crate) column: usize,
}

impl Position {
    pub(crate) fn new() -> Self {
        Self { line: 1, column: 0 }
    }
}

#[derive(Debug)]
pub(crate) struct PositionRange {
    pub(crate) start: Position, // inclusive
    pub(crate) end: Position,   // exclusive
}

#[derive(Debug)]
pub(crate) struct Token {
    pub(crate) kind: TokenKind,
    pub(crate) string_range: ByteRange,
    pub(crate) position_range: PositionRange,
}

#[derive(Debug)]
pub(crate) struct TokenInfo {
    pub(crate) token: Token,
    pub(crate) line_range: ByteRange,
}

pub(crate) type KeywordMap = Trie<u8>;
