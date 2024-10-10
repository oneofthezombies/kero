struct File {
    path: String,
    content: String,
}

struct Lexer<'a> {
    file: &'a File,
}

impl<'a> Lexer<'a> {
    fn tokenize() {
        println!("hello")
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tokenize() {}
}
