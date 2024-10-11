pub fn is_number(c: u8) -> bool {
    if c < b'0' {
        return false;
    }

    if c > b'9' {
        return false;
    }

    return true;
}

pub fn is_alpha_lower(c: u8) -> bool {
    if c < b'a' {
        return false;
    }

    if c > b'z' {
        return false;
    }

    return true;
}

pub fn is_alpha_upper(c: u8) -> bool {
    if c < b'A' {
        return false;
    }

    if c > b'Z' {
        return false;
    }

    return true;
}

pub fn is_underscore(c: u8) -> bool {
    c == b'_'
}

pub fn is_carriage_return(c: u8) -> bool {
    c == b'\r'
}

pub fn is_line_feed(c: u8) -> bool {
    c == b'\n'
}

pub fn is_whitespace(c: u8) -> bool {
    c == b' ' || c == b'\t'
}

pub fn is_leading_byte(byte: u8) -> bool {
    !is_continuation_byte(byte)
}

pub fn is_continuation_byte(byte: u8) -> bool {
    byte & 0b1100_0000 == 0b1000_0000
}

pub fn utf8_byte_len(leading_byte: u8) -> Option<usize> {
    if leading_byte & 0b1000_0000 == 0 {
        Some(1)
    } else if leading_byte & 0b1110_0000 == 0b1100_0000 {
        Some(2)
    } else if leading_byte & 0b1111_0000 == 0b1110_0000 {
        Some(3)
    } else if leading_byte & 0b1111_1000 == 0b1111_0000 {
        Some(4)
    } else {
        // continuation byte or invalid byte
        None
    }
}
