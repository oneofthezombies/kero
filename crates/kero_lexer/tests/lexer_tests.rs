use anyhow::{bail, Result};
use core::str;
use kero_lexer::{
    core::{TokenInfo, TokenKind},
    lexer::Lexer,
};

struct CheckInfo<'a> {
    source: &'a [u8],
    info: &'a TokenInfo,
    kind: TokenKind,
    string_range: (usize, usize),
    string: &'a [u8],
    position_range: ((usize, usize), (usize, usize)),
    line_range: (usize, usize),
    line: &'a [u8],
}

fn check_info(check_info: CheckInfo) -> Result<()> {
    if check_info.info.token.kind != check_info.kind {
        bail!(
            "kind real: {:?} expected: {:?}",
            check_info.info.token.kind,
            check_info.kind
        );
    }
    if check_info.info.token.string_range.start != check_info.string_range.0 {
        bail!(
            "string_range.start real: {} expected: {}",
            check_info.info.token.string_range.start,
            check_info.string_range.0,
        );
    }
    if check_info.info.token.string_range.end != check_info.string_range.1 {
        bail!(
            "string_range.end real: {} expected: {}",
            check_info.info.token.string_range.end,
            check_info.string_range.1,
        );
    }
    if &check_info.source[check_info.string_range.0..check_info.string_range.1] != check_info.string
    {
        bail!(
            "string real: {} expected: {}",
            str::from_utf8(
                &check_info.source[check_info.string_range.0..check_info.string_range.1],
            )?,
            str::from_utf8(check_info.string)?,
        );
    }
    if check_info.info.token.position_range.start.line != check_info.position_range.0 .0 {
        bail!(
            "position_range.start.line real: {} expected: {}",
            check_info.info.token.position_range.start.line,
            check_info.position_range.0 .0,
        );
    }
    if check_info.info.token.position_range.start.column != check_info.position_range.0 .1 {
        bail!(
            "position_range.start.column real: {} expected: {}",
            check_info.info.token.position_range.start.column,
            check_info.position_range.0 .1,
        );
    }
    if check_info.info.token.position_range.end.line != check_info.position_range.1 .0 {
        bail!(
            "position_range.end.line real: {} expected: {}",
            check_info.info.token.position_range.end.line,
            check_info.position_range.1 .0,
        );
    }
    if check_info.info.token.position_range.end.column != check_info.position_range.1 .1 {
        bail!(
            "position_range.end.line real: {} expected: {}",
            check_info.info.token.position_range.end.column,
            check_info.position_range.1 .1,
        );
    }
    if check_info.info.line_range.start != check_info.line_range.0 {
        bail!(
            "line_range.start real: {} expected: {}",
            check_info.info.line_range.start,
            check_info.line_range.0,
        );
    }
    if check_info.info.line_range.end != check_info.line_range.1 {
        bail!(
            "line_range.end real: {} expected: {}",
            check_info.info.line_range.end,
            check_info.line_range.1,
        );
    }
    if &check_info.source[check_info.line_range.0..check_info.line_range.1] != check_info.line {
        bail!(
            "line real: {} expected: {}",
            str::from_utf8(&check_info.source[check_info.line_range.0..check_info.line_range.1])?,
            str::from_utf8(check_info.line)?,
        );
    }
    Ok(())
}

#[test]
fn endmarker() {
    let source = b"";
    let mut lexer = Lexer::new(source.as_slice());
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
    })
    .unwrap();
}

#[test]
fn nl_carriage_return() {
    let source = b"\r";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn nl_line_feed() {
    let source = b"\n";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn nl_carriage_return_line_feed() {
    let source = b"\r\n";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
    }
}

#[test]
fn comment() {
    let source = b"#";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
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
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn comment_carriage_return() {
    let source = b"#\r";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
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
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn comment_line_feed() {
    let source = b"#\n";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
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
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn comment_carriage_return_line_feed() {
    let source = b"#\r\n";
    let mut lexer = Lexer::new(source.as_slice());
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
        })
        .unwrap();
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
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn name_ascii_start() {
    let source = b"a";
    let mut lexer = Lexer::new(source.as_slice());
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Name,
            string_range: (0, 1),
            string: b"a",
            position_range: ((1, 0), (1, 1)),
            line_range: (0, 1),
            line: b"a",
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Newline,
            string_range: (1, 1),
            string: b"",
            position_range: ((1, 1), (1, 2)),
            line_range: (0, 1),
            line: b"a",
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn name_ascii_continue_ascii() {
    let source = b"a1";
    let mut lexer = Lexer::new(source.as_slice());
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Name,
            string_range: (0, 2),
            string: b"a1",
            position_range: ((1, 0), (1, 2)),
            line_range: (0, 2),
            line: b"a1",
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Newline,
            string_range: (2, 2),
            string: b"",
            position_range: ((1, 2), (1, 3)),
            line_range: (0, 2),
            line: b"a1",
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn name_ascii_continue_multi_byte_code_point() {
    let source_str = "a가";
    let source = source_str.as_bytes();
    let mut lexer = Lexer::new(source);
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Name,
            string_range: (0, 4),
            string: "a가".as_bytes(),
            position_range: ((1, 0), (1, 4)),
            line_range: (0, 4),
            line: "a가".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Newline,
            string_range: (4, 4),
            string: b"",
            position_range: ((1, 4), (1, 5)),
            line_range: (0, 4),
            line: "a가".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Endmarker,
            string_range: (4, 4),
            string: b"",
            position_range: ((2, 0), (2, 0)),
            line_range: (4, 4),
            line: b"",
        })
        .unwrap();
    }
}

#[test]
fn name_utf8_multi_byte_code_point_start() {
    let source_str = "가";
    let source = source_str.as_bytes();
    let mut lexer = Lexer::new(source);
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Name,
            string_range: (0, 3),
            string: "가".as_bytes(),
            position_range: ((1, 0), (1, 3)),
            line_range: (0, 3),
            line: "가".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Newline,
            string_range: (3, 3),
            string: b"",
            position_range: ((1, 3), (1, 4)),
            line_range: (0, 3),
            line: "가".as_bytes(),
        })
        .unwrap();
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
        })
        .unwrap();
    }
}

#[test]
fn name_utf8_multi_byte_code_point_continue_ascii() {
    let source_str = "가1";
    let source = source_str.as_bytes();
    let mut lexer = Lexer::new(source);
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Name,
            string_range: (0, 4),
            string: "가1".as_bytes(),
            position_range: ((1, 0), (1, 4)),
            line_range: (0, 4),
            line: "가1".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Newline,
            string_range: (4, 4),
            string: b"",
            position_range: ((1, 4), (1, 5)),
            line_range: (0, 4),
            line: "가1".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Endmarker,
            string_range: (4, 4),
            string: b"",
            position_range: ((2, 0), (2, 0)),
            line_range: (4, 4),
            line: b"",
        })
        .unwrap();
    }
}

#[test]
fn name_utf8_multi_byte_code_point_continue_multi_byte_code_point() {
    let source_str = "가나";
    let source = source_str.as_bytes();
    let mut lexer = Lexer::new(source);
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Name,
            string_range: (0, 6),
            string: "가나".as_bytes(),
            position_range: ((1, 0), (1, 6)),
            line_range: (0, 6),
            line: "가나".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Newline,
            string_range: (6, 6),
            string: b"",
            position_range: ((1, 6), (1, 7)),
            line_range: (0, 6),
            line: "가나".as_bytes(),
        })
        .unwrap();
    }
    {
        let info = lexer.next().unwrap();
        check_info(CheckInfo {
            source,
            info: &info,
            kind: TokenKind::Endmarker,
            string_range: (6, 6),
            string: b"",
            position_range: ((2, 0), (2, 0)),
            line_range: (6, 6),
            line: b"",
        })
        .unwrap();
    }
}
