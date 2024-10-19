use std::{mem::MaybeUninit, usize};

pub(crate) struct StackCircularBuffer<const N: usize, T> {
    buf: [MaybeUninit<T>; N],
    head: usize,
    tail: usize,
    is_full: bool,
}

impl<const N: usize, T> StackCircularBuffer<N, T> {
    pub(crate) fn new() -> Self {
        Self {
            buf: unsafe { MaybeUninit::uninit().assume_init() },
            head: 0,
            tail: 0,
            is_full: false,
        }
    }

    pub(crate) fn capacity(&self) -> usize {
        N
    }

    pub(crate) fn len(&self) -> usize {
        if self.head > self.tail {
            self.head - self.tail
        } else {
            self.tail - self.head
        }
    }

    pub(crate) fn is_empty(&self) -> bool {
        self.head == self.tail && !self.is_full
    }

    pub(crate) fn get(&self, index: usize) -> Option<&T> {
        debug_assert!(self.head < N);
        debug_assert!(self.tail < N);
        todo!();
    }

    pub(crate) fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        debug_assert!(self.head < N);
        debug_assert!(self.tail < N);

        todo!();
    }

    pub(crate) fn front(&self) -> Option<&T> {
        self.get(self.head)
    }

    pub(crate) fn front_mut(&mut self) -> Option<&mut T> {
        self.get_mut(self.head)
    }

    pub(crate) fn back(&self) -> Option<&T> {
        let index = if self.tail > 0 { self.tail - 1 } else { N - 1 };
        self.get(index)
    }

    pub(crate) fn back_mut(&mut self) -> Option<&mut T> {
        todo!();
    }

    pub(crate) fn pop_front(&mut self) -> Option<T> {
        todo!();
    }

    pub(crate) fn push_back(&mut self, value: T) {
        todo!();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn capacity() {}

    #[test]
    fn len() {}

    #[test]
    fn is_empty() {}

    #[test]
    fn get() {}

    #[test]
    fn get_mut() {}

    #[test]
    fn front() {}

    #[test]
    fn front_mut() {}

    #[test]
    fn back() {}

    #[test]
    fn back_mut() {}

    #[test]
    fn pop_front() {}

    #[test]
    fn push_back() {}
}
