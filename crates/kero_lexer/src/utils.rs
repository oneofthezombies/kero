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
