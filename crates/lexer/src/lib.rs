pub struct Source {
    file_path: String,
    file_content: String,
}

pub fn tokenize(source: &Source) {
    println!("{}", source.file_path);
    println!("{}", source.file_content)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tokenize() {
        tokenize(&Source {
            file_path: "".to_string(),
            file_content: "".to_string(),
        })
    }
}
