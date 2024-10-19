use anyhow::{bail, Result};
use std::{mem::MaybeUninit, usize};

pub(crate) struct CircularBuffer<const N: usize, T> {
    buf: [MaybeUninit<T>; N],
    head: usize,
    tail: usize,
    is_full: bool,
}

impl<const N: usize, T> CircularBuffer<N, T> {
    pub(crate) fn try_new() -> Result<Self> {
        if N == 0 {
            bail!("Buffer size must be greater than 0.");
        };
        Ok(Self {
            buf: unsafe { MaybeUninit::uninit().assume_init() },
            head: 0,
            tail: 0,
            is_full: false,
        })
    }

    pub(crate) fn capacity(&self) -> usize {
        N
    }

    pub(crate) fn len(&self) -> usize {
        if self.head == self.tail {
            if self.is_full {
                N
            } else {
                0
            }
        } else if self.head < self.tail {
            self.tail - self.head
        } else {
            // tail < head
            N - self.head + self.tail
        }
    }

    pub(crate) fn is_empty(&self) -> bool {
        self.head == self.tail && !self.is_full
    }

    pub(crate) fn get(&self, index: usize) -> Option<&T> {
        self.buf
            .get(self.parse_index(index)?)
            .map(|v| unsafe { v.assume_init_ref() })
    }

    pub(crate) fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        let index = self.parse_index(index)?;
        self.buf
            .get_mut(index)
            .map(|v| unsafe { v.assume_init_mut() })
    }

    pub(crate) fn front(&self) -> Option<&T> {
        self.get(0)
    }

    pub(crate) fn front_mut(&mut self) -> Option<&mut T> {
        self.get_mut(0)
    }

    pub(crate) fn back(&self) -> Option<&T> {
        self.get(self.len().wrapping_sub(1))
    }

    pub(crate) fn back_mut(&mut self) -> Option<&mut T> {
        self.get_mut(self.len().wrapping_sub(1))
    }

    pub(crate) fn pop_front(&mut self) -> Option<T> {
        if self.is_empty() {
            return None;
        }
        let value = unsafe { self.buf[self.head].assume_init_read() };
        debug_assert!(N != 0);
        self.head = self.head.wrapping_add(1) % N;
        self.is_full = false;
        Some(value)
    }

    #[must_use]
    pub(crate) fn push_back(&mut self, value: T) -> bool {
        if self.is_full {
            return false;
        }
        self.buf[self.tail] = MaybeUninit::new(value);
        debug_assert!(N != 0);
        self.tail = self.tail.wrapping_add(1) % N;
        if self.tail == self.head {
            self.is_full = true;
        }
        true
    }

    fn parse_index(&self, index: usize) -> Option<usize> {
        debug_assert!(N != 0);
        let index = self.head.wrapping_add(index) % N;
        if self.head == self.tail {
            if self.is_full {
                Some(index)
            } else {
                None
            }
        } else if self.head < self.tail {
            if self.head <= index && index < self.tail {
                Some(index)
            } else {
                None
            }
        } else {
            // tail < head
            if self.head <= index && index < N {
                Some(index)
            } else {
                if index < self.tail {
                    Some(index)
                } else {
                    None
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn wrapping_add() {
        assert_eq!(usize::MAX.wrapping_add(1), 0);
    }

    #[test]
    fn wrapping_sub() {
        assert_eq!(0usize.wrapping_sub(1), usize::MAX);
    }

    #[test]
    fn n_0() {
        let result = CircularBuffer::<0, i32>::try_new();
        assert_eq!(result.is_err(), true);
    }

    #[test]
    fn n_1() {
        let result = CircularBuffer::<1, i32>::try_new();
        assert_eq!(result.is_ok(), true);
    }

    #[test]
    fn n_2() {
        let result = CircularBuffer::<2, i32>::try_new();
        assert_eq!(result.is_ok(), true);
    }

    #[test]
    fn capacity_1() {
        let result = CircularBuffer::<1, i32>::try_new();
        let buf = result.unwrap();
        assert_eq!(buf.capacity(), 1);
    }

    #[test]
    fn capacity_2() {
        let result = CircularBuffer::<2, i32>::try_new();
        let buf = result.unwrap();
        assert_eq!(buf.capacity(), 2);
    }

    #[test]
    fn len_empty() {
        let result = CircularBuffer::<1, i32>::try_new();
        let buf = result.unwrap();
        assert_eq!(buf.len(), 0);
    }

    #[test]
    fn len_full() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.len(), 1);
    }

    #[test]
    fn len_head_smaller_than_tail() {
        let result = CircularBuffer::<2, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.len(), 1);
    }

    #[test]
    fn len_tail_smaller_than_head() {
        let result = CircularBuffer::<2, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.push_back(1), true);
        assert_eq!(buf.pop_front().is_some(), true);
        assert_eq!(buf.len(), 1);
    }

    #[test]
    fn is_empty() {
        let result = CircularBuffer::<2, i32>::try_new();
        let buf = result.unwrap();
        assert_eq!(buf.is_empty(), true);
    }

    #[test]
    fn get_0() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.get(0), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.get(0), Some(0).as_ref());
    }

    #[test]
    fn get_mut() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.get_mut(0), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.get_mut(0), Some(0).as_mut());
    }

    #[test]
    fn front() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.front(), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.front(), Some(0).as_ref());
    }

    #[test]
    fn front_mut() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.front_mut(), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.front_mut(), Some(0).as_mut());
    }

    #[test]
    fn back() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.back(), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.back(), Some(0).as_ref());
    }

    #[test]
    fn back_mut() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.back_mut(), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.back_mut(), Some(0).as_mut());
    }

    #[test]
    fn pop_front() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.pop_front(), None);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.pop_front(), Some(0));
        assert_eq!(buf.pop_front(), None);
    }

    #[test]
    fn push_back() {
        let result = CircularBuffer::<1, i32>::try_new();
        let mut buf = result.unwrap();
        assert_eq!(buf.is_empty(), true);
        assert_eq!(buf.push_back(0), true);
        assert_eq!(buf.front(), Some(0).as_ref());
        assert_eq!(buf.back(), Some(0).as_ref());
        assert_eq!(buf.is_empty(), false);
    }
}
