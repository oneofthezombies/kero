use core::hash::Hash;
use std::collections::HashMap;

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

    pub fn insert(&mut self, sequence: &[T]) -> &mut Self {
        let mut current = &mut self.root;
        for element in sequence {
            current = current
                .children
                .entry(element.clone())
                .or_insert_with(Node::new);
        }
        current.is_end = true;
        self
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

    pub fn match_full(&self, sequence: &[T]) -> bool {
        let mut current = &self.root;
        for element in sequence {
            let Some(child) = current.children.get(element) else {
                return false;
            };
            current = child;
        }
        current.is_end
    }

    pub fn match_prefix(&self, sequence: &[T]) -> bool {
        if sequence.len() == 0 {
            return false;
        }

        let mut current = &self.root;
        for element in sequence {
            let Some(child) = current.children.get(element) else {
                return false;
            };
            current = child;
        }
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn match_full_no_exist_length_0() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        assert!(!trie.match_full(b""));
    }

    #[test]
    fn match_full_no_exist_length_1() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        assert!(!trie.match_full(b"a"));
    }

    #[test]
    fn match_full_no_exist_length_2() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        assert!(!trie.match_full(b"aa"));
    }

    #[test]
    fn match_full_exist_length_1_length_0() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"a");
        let trie = builder.build();
        assert!(!trie.match_full(b""));
    }

    #[test]
    fn match_full_exist_length_1_length_1() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"a");
        let trie = builder.build();
        assert!(trie.match_full(b"a"));
    }

    #[test]
    fn match_full_exist_length_1_length_2() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"a");
        let trie = builder.build();
        assert!(!trie.match_full(b"aa"));
    }

    #[test]
    fn match_full_exist_length_2_length_0() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"aa");
        let trie = builder.build();
        assert!(!trie.match_full(b""));
    }

    #[test]
    fn match_full_exist_length_2_length_1() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"aa");
        let trie = builder.build();
        assert!(!trie.match_full(b"a"));
    }

    #[test]
    fn match_full_exist_length_2_length_2() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"aa");
        let trie = builder.build();
        assert!(trie.match_full(b"aa"));
    }

    #[test]
    fn match_prefix_no_exist_length_0() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        assert!(!trie.match_prefix(b""));
    }

    #[test]
    fn match_prefix_no_exist_length_1() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        assert!(!trie.match_prefix(b"a"));
    }

    #[test]
    fn match_prefix_no_exist_length_2() {
        let builder = TrieBuilder::new();
        let trie = builder.build();
        assert!(!trie.match_prefix(b"aa"));
    }

    #[test]
    fn match_prefix_exist_length_1_length_0() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"a");
        let trie = builder.build();
        assert!(!trie.match_prefix(b""));
    }

    #[test]
    fn match_prefix_exist_length_1_length_1() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"a");
        let trie = builder.build();
        assert!(trie.match_prefix(b"a"));
    }

    #[test]
    fn match_prefix_exist_length_1_length_2() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"a");
        let trie = builder.build();
        assert!(!trie.match_prefix(b"aa"));
    }

    #[test]
    fn match_prefix_exist_length_2_length_0() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"aa");
        let trie = builder.build();
        assert!(!trie.match_prefix(b""));
    }

    #[test]
    fn match_prefix_exist_length_2_length_1() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"aa");
        let trie = builder.build();
        assert!(trie.match_prefix(b"a"));
    }

    #[test]
    fn match_prefix_exist_length_2_length_2() {
        let mut builder = TrieBuilder::new();
        builder.insert(b"aa");
        let trie = builder.build();
        assert!(trie.match_prefix(b"aa"));
    }
}
