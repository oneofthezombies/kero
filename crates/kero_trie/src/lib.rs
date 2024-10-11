use core::hash::Hash;
use std::collections::HashMap;

#[derive(Debug, PartialEq)]
pub enum TrieError {
    SequenceIsEmpty,
    SequenceNotExist,
    SequenceNotFullMatch,
}

impl std::error::Error for TrieError {}

impl core::fmt::Display for TrieError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            TrieError::SequenceIsEmpty => write!(f, "Sequence is empty"),
            TrieError::SequenceNotExist => write!(f, "Sequence not exist"),
            TrieError::SequenceNotFullMatch => write!(f, "Sequence not full match"),
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

    pub fn match_full(&self, sequence: &[T]) -> Result<(), TrieError> {
        match self.match_internal(sequence) {
            Ok(v) => {
                if v {
                    Ok(())
                } else {
                    Err(TrieError::SequenceNotFullMatch)
                }
            }
            Err(e) => Err(e),
        }
    }

    pub fn match_prefix(&self, sequence: &[T]) -> Result<(), TrieError> {
        match self.match_internal(sequence) {
            Ok(_) => Ok(()),
            Err(e) => Err(e),
        }
    }

    fn match_internal(&self, sequence: &[T]) -> Result<bool, TrieError> {
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

        Ok(current.is_end)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_match_full_sequence_is_empty() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        let result = trie.match_full("".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceIsEmpty)
    }

    #[test]
    fn test_match_full_sequence_not_exist() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        let result = trie.match_full("a".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceNotExist)
    }

    #[test]
    fn test_match_full_sequence_not_full_match() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.match_full("a".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceNotFullMatch);
    }

    #[test]
    fn test_match_full_same_a() {
        let mut builder = TrieBuilder::new();
        builder.push("a".as_bytes());
        let trie = builder.build();
        let result = trie.match_full("a".as_bytes());
        assert!(result.is_ok())
    }

    #[test]
    fn test_match_full_same_aa() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.match_full("aa".as_bytes());
        assert!(result.is_ok());
    }

    #[test]
    fn test_match_full_same_aaa() {
        let mut builder = TrieBuilder::new();
        builder.push("aaa".as_bytes());
        let trie = builder.build();
        let result = trie.match_full("aaa".as_bytes());
        assert!(result.is_ok());
    }

    #[test]
    fn test_match_prefix_partial() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.match_prefix("a".as_bytes());
        assert!(result.is_ok());
    }

    #[test]
    fn test_match_prefix_same() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.match_prefix("aa".as_bytes());
        assert!(result.is_ok());
    }

    #[test]
    fn test_match_prefix_sequence_is_empty() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.match_prefix("".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceIsEmpty);
    }

    #[test]
    fn test_match_prefix_sequence_not_exist() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.match_prefix("aaa".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::SequenceNotExist);
    }
}
