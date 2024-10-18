use crate::utf8::unchecked::ByteKind;

pub(crate) mod unchecked {
    #[derive(Debug)]
    pub(crate) enum ByteKind {
        Ascii,
        Continuation,
        FirstOf2ByteCodePoint,
        FirstOf3ByteCodePoint,
        FirstOf4ByteCodePoint,
        Unexpected,
    }

    impl ByteKind {
        pub(crate) fn from(byte: u8) -> ByteKind {
            match byte {
                0x00..=0x7F => ByteKind::Ascii,
                0x80..=0xBF => ByteKind::Continuation,
                0xC0..=0xDF => ByteKind::FirstOf2ByteCodePoint,
                0xE0..=0xEF => ByteKind::FirstOf3ByteCodePoint,
                0xF0..=0xF7 => ByteKind::FirstOf4ByteCodePoint,
                _ => ByteKind::Unexpected,
            }
        }

        pub(crate) fn is_first_of_multi_byte_code_point(&self) -> bool {
            match self {
                ByteKind::FirstOf2ByteCodePoint
                | ByteKind::FirstOf3ByteCodePoint
                | ByteKind::FirstOf4ByteCodePoint => true,
                ByteKind::Ascii | ByteKind::Continuation | ByteKind::Unexpected => false,
            }
        }

        pub(crate) fn trailing_byte_count(&self) -> Option<usize> {
            match self {
                ByteKind::Ascii => Some(0),
                ByteKind::FirstOf2ByteCodePoint => Some(1),
                ByteKind::FirstOf3ByteCodePoint => Some(2),
                ByteKind::FirstOf4ByteCodePoint => Some(3),
                ByteKind::Continuation | ByteKind::Unexpected => None,
            }
        }
    }
}

impl From<u8> for ByteKind {
    fn from(byte: u8) -> Self {
        ByteKind::from(byte)
    }
}
