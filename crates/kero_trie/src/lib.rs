use core::hash::Hash;
use std::collections::HashMap;

#[derive(Debug, PartialEq)]
pub enum TrieError {
    ElementsIsEmpty,
}

impl std::error::Error for TrieError {}

impl core::fmt::Display for TrieError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            TrieError::ElementsIsEmpty => write!(f, "Elements is empty"),
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

    pub fn push(&mut self, elements: &[T]) {
        let mut current = &mut self.root;
        for element in elements {
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

    pub fn exact_match(&self, elements: &[T]) -> Result<bool, TrieError> {
        if elements.is_empty() {
            return Err(TrieError::ElementsIsEmpty);
        }
        let mut current = &self.root;
        for element in elements {
            let Some(child) = current.children.get(element) else {
                return Ok(false);
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
    fn test_empty_elements() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        let result = trie.exact_match("".as_bytes());
        assert_eq!(result.unwrap_err(), TrieError::ElementsIsEmpty)
    }

    #[test]
    fn test_not_exist() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        let result = trie.exact_match("a".as_bytes());
        assert!(!result.unwrap());
    }

    #[test]
    fn test_exact_match_a() {
        let mut builder = TrieBuilder::new();
        builder.push("a".as_bytes());
        let trie = builder.build();
        let result = trie.exact_match("a".as_bytes());
        assert!(result.unwrap());
    }

    #[test]
    fn test_exact_match_aa() {
        let mut builder = TrieBuilder::new();
        builder.push("aa".as_bytes());
        let trie = builder.build();
        let result = trie.exact_match("aa".as_bytes());
        assert!(result.unwrap());
    }

    #[test]
    fn test_exact_match_aaa() {
        let mut builder = TrieBuilder::new();
        builder.push("aaa".as_bytes());
        let trie = builder.build();
        let result = trie.exact_match("aaa".as_bytes());
        assert!(result.unwrap());
    }
}
