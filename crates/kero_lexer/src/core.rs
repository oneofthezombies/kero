#[derive(Clone, Debug, PartialEq)]
pub enum TokenKind {
    Endmarker, // EOF
    Newline,
    Nl,
    Indent,
    Dedent,
    Comment, // #
    Name,    // identifier or keyword
    String,  // "" '' """""" ''''''
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
