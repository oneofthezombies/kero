pub fn is_number(byte: u8) -> bool {
    b'0' <= byte && byte <= b'9'
}

pub fn is_alpha_lower(byte: u8) -> bool {
    b'a' <= byte && byte <= b'z'
}

pub fn is_alpha_upper(byte: u8) -> bool {
    b'A' <= byte && byte <= b'Z'
}

pub fn is_underscore(byte: u8) -> bool {
    byte == b'_'
}

pub fn is_carriage_return(byte: u8) -> bool {
    byte == b'\r'
}

pub fn is_line_feed(byte: u8) -> bool {
    byte == b'\n'
}

pub fn is_space(byte: u8) -> bool {
    byte == b' '
}

pub fn is_tab(byte: u8) -> bool {
    byte == b'\t'
}

pub fn is_hyphen(byte: u8) -> bool {
    byte == b'-'
}

pub fn is_single_quote(byte: u8) -> bool {
    byte == b'\''
}

pub fn is_double_quote(byte: u8) -> bool {
    byte == b'"'
}

mod utf8 {
    pub enum ByteKind {
        Leading1,
        Leading2,
        Leading3,
        Leading4,
        Continuation,
        Unknown,
    }

    pub fn get_byte_kind(byte: u8) -> ByteKind {
        match byte {
            b if b & 0b1000_0000 == 0 => ByteKind::Leading1,
            b if b & 0b1110_0000 == 0b1100_0000 => ByteKind::Leading2,
            b if b & 0b1111_0000 == 0b1110_0000 => ByteKind::Leading3,
            b if b & 0b1111_1000 == 0b1111_0000 => ByteKind::Leading4,
            b if b & 0b1100_0000 == 0b1000_0000 => ByteKind::Continuation,
            _ => ByteKind::Unknown,
        }
    }
}
