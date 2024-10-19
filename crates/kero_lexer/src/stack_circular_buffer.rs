use std::{mem::MaybeUninit, usize};

pub(crate) struct StackCircularBuffer<const N: usize, T> {
    buf: [MaybeUninit<T>; N],
    head: usize,
    tail: usize,
    is_full: bool,
}

impl<const N: usize, T> StackCircularBuffer<N, T> {
    pub(crate) fn new() -> Self {
        debug_assert!(N > 0);
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
        if self.is_full {
            N
        } else {
            if self.tail > self.head {
                self.tail - self.head
            } else {
                N - self.head + self.tail
            }
        }
    }

    pub(crate) fn is_empty(&self) -> bool {
        self.head == self.tail && !self.is_full
    }

    pub(crate) fn get(&self, index: usize) -> Option<&T> {
        self.buf
            .get(self.buf_index(index))
            .map(|v| unsafe { v.assume_init_ref() })
    }

    pub(crate) fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        let buf_index = self.buf_index(index);
        self.buf
            .get_mut(buf_index)
            .map(|v| unsafe { v.assume_init_mut() })
    }

    pub(crate) fn front(&self) -> Option<&T> {
        self.get(0)
    }

    pub(crate) fn front_mut(&mut self) -> Option<&mut T> {
        self.get_mut(0)
    }

    pub(crate) fn back(&self) -> Option<&T> {
        self.get(N - 1)
    }

    pub(crate) fn back_mut(&mut self) -> Option<&mut T> {
        self.get_mut(N - 1)
    }

    pub(crate) fn pop_front(&mut self) -> Option<T> {
        todo!();
    }

    pub(crate) fn push_back(&mut self, value: T) {
        todo!();
    }

    fn buf_index(&self, index: usize) -> usize {
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
