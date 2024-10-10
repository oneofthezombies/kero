use core::hash::Hash;
use std::collections::HashMap;

#[derive(Debug, PartialEq)]
pub enum TrieError {
    SequenceIsEmpty,
    SequenceNotExist,
}

impl std::error::Error for TrieError {}

impl core::fmt::Display for TrieError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            TrieError::SequenceIsEmpty => write!(f, "Sequence is empty"),
            TrieError::SequenceNotExist => write!(f, "Sequence not exist"),
        }
    }
}

pub struct Node<T> {
    children: HashMap<T, Node<T>>,
    is_end: bool,
}

impl<T> Node<T>
where
    T: Eq + Hash,
{
    fn new() -> Self {
        Self {
            children: HashMap::new(),
            is_end: false,
        }
    }
}

pub struct TrieBuilder<T> {
    root: Node<T>,
}

impl<T> TrieBuilder<T>
where
    T: Eq + Hash + Clone,
{
    pub fn new() -> Self {
        Self { root: Node::new() }
    }

    pub fn push(&mut self, sequence: &[T]) {
        let mut current = &mut self.root;
        for element in sequence {
            current = current
                .children
                .entry(element.clone())
                .or_insert_with(Node::new);
        }
        current.is_end = true;
    }

    pub fn build(self) -> Trie<T> {
        return Trie { root: self.root };
    }
}

pub struct Trie<T> {
    root: Node<T>,
}

impl<T> Trie<T>
where
    T: Eq + Hash,
{
    pub fn new(root: Node<T>) -> Self {
        Self { root }
    }

    pub fn exact_match(&self, sequence: &[T]) -> Result<(), TrieError> {
        if sequence.is_empty() {
            return Err(TrieError::SequenceIsEmpty);
        }

        let mut current = &self.root;
        for element in sequence {
            let Some(child) = current.children.get(element) else {
                return Err(TrieError::SequenceNotExist);
            };
            current = child;
        }

        if !current.is_end {
            return Err(TrieError::SequenceNotExist);
        }

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_sequence_is_empty() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        let result = trie.exact_match("".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceIsEmpty)
    }

    #[test]
    fn test_sequence_not_exist() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        let result = trie.exact_match("a".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceNotExist)
    }

    #[test]
    fn test_exact_match_a() {
        let mut builder = TrieBuilder::new();
        builder.push("a".as_bytes());
        let trie = builder.build();
        let result = trie.exact_match("a".as_bytes());
        assert!(result.is_ok())
    }

    #[test]
    fn test_exact_match_aa() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.exact_match("aa".as_bytes());
        assert!(result.is_ok());
    }

    #[test]
    fn test_exact_match_aaa() {
        let mut builder = TrieBuilder::new();
        builder.push("aaa".as_bytes());
        let trie = builder.build();
        let result = trie.exact_match("aaa".as_bytes());
        assert!(result.is_ok());
    }
}
