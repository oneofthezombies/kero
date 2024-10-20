use anyhow::{bail, Result};
use std::{mem::MaybeUninit, usize};

pub(crate) struct CircularBuffer<T, const N: usize> {
    buf: [MaybeUninit<T>; N],
    head: usize,
    tail: usize,
    is_full: bool,
}

impl<T, const N: usize> CircularBuffer<T, N> {
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
        } else
        /* tail < head */
        {
            N - self.head + self.tail
        }
    }

    pub(crate) fn is_empty(&self) -> bool {
        self.head == self.tail && !self.is_full
    }

    pub(crate) fn get(&self, index: usize) -> Option<&T> {
        self.buf
            .get(self.parse_index_to_position(index)?)
            .map(|v| unsafe { v.assume_init_ref() })
    }

    pub(crate) fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        let position = self.parse_index_to_position(index)?;
        self.buf
            .get_mut(position)
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

    fn parse_index_to_position(&self, index: usize) -> Option<usize> {
        debug_assert!(N != 0);
        let position = self.head.wrapping_add(index) % N;
        if self.head == self.tail {
            if self.is_full {
                Some(position)
            } else {
                None
            }
        } else if self.head < self.tail {
            if self.head <= position && position < self.tail {
                Some(position)
            } else {
                None
            }
        } else
        /* tail < head */
        {
            if self.head <= position && position < N {
                Some(position)
            } else {
                if position < self.tail {
                    Some(position)
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
    use core::fmt;

    struct Check<T, const N: usize> {
        capacity: usize,
        len: usize,
        is_empty: bool,
        front: Option<T>,
        back: Option<T>,
        values: [Option<T>; N],
    }

    fn check<T, const N: usize>(
        buf: &mut CircularBuffer<T, N>,
        mut check: Check<T, N>,
    ) -> Result<()>
    where
        T: fmt::Debug + PartialEq,
    {
        if buf.capacity() != check.capacity {
            bail!(
                "capacity real: {} expect: {}",
                buf.capacity(),
                check.capacity
            );
        }
        if buf.len() != check.len {
            bail!("len real: {} expect: {}", buf.len(), check.len);
        }
        if buf.is_empty() != check.is_empty {
            bail!(
                "is_empty real: {} expect: {}",
                buf.is_empty(),
                check.is_empty
            );
        }
        if buf.front() != check.front.as_ref() {
            bail!(
                "front real: {:?} expect: {:?}",
                buf.front(),
                check.front.as_ref()
            );
        }
        if buf.front_mut() != check.front.as_mut() {
            bail!(
                "front_mut real: {:?} expect: {:?}",
                buf.front_mut(),
                check.front.as_mut()
            );
        }
        if buf.back() != check.back.as_ref() {
            bail!(
                "back real: {:?} expect: {:?}",
                buf.back(),
                check.back.as_ref()
            );
        }
        if buf.back_mut() != check.back.as_mut() {
            bail!(
                "back_mut real: {:?} expect: {:?}",
                buf.back_mut(),
                check.back.as_mut()
            )
        }
        for i in 0..check.capacity {
            if buf.get(i) != check.values.get(i).unwrap().as_ref() {
                bail!(
                    "get({}) real: {:?} expect: {:?}",
                    i,
                    buf.get(i),
                    check.values.get(i)
                );
            }
            if buf.get_mut(i) != check.values.get_mut(i).unwrap().as_mut() {
                bail!(
                    "get_mut({}) real: {:?} expect: {:?}",
                    i,
                    buf.get_mut(i),
                    check.values.get_mut(i)
                );
            }
        }
        Ok(())
    }

    macro_rules! check {
        ($buf:expr, $check:expr) => {
            check($buf, $check).unwrap()
        };
    }

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
        let result = CircularBuffer::<i32, 0>::try_new();
        assert_eq!(result.is_err(), true);
    }

    #[test]
    fn n_1() {
        let mut buf = CircularBuffer::<i32, 1>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
    }

    #[test]
    fn n_1_push_back_once() {
        let mut buf = CircularBuffer::<i32, 1>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0)]
            }
        );
    }

    #[test]
    fn n_1_push_back_twice() {
        let mut buf = CircularBuffer::<i32, 1>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0)]
            }
        );
        assert_eq!(buf.push_back(1), false);
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0)]
            }
        );
    }

    #[test]
    fn n_1_push_back_once_pop_front_once() {
        let mut buf = CircularBuffer::<i32, 1>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0)]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
    }

    #[test]
    fn n_1_push_back_once_pop_front_twice() {
        let mut buf = CircularBuffer::<i32, 1>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0)]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
        assert_eq!(buf.pop_front(), None);
        check!(
            &mut buf,
            Check {
                capacity: 1,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None]
            }
        );
    }

    #[test]
    fn n_2() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        )
    }

    #[test]
    fn n_2_push_back_once() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
    }

    #[test]
    fn n_2_push_back_twice() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.push_back(1), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 2,
                is_empty: false,
                front: Some(0),
                back: Some(1),
                values: [Some(0), Some(1)]
            }
        );
    }

    #[test]
    fn n_2_push_back_once_pop_front_once() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
    }

    #[test]
    fn n_2_push_back_once_pop_front_twice() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.pop_front(), None);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
    }

    #[test]
    fn n_2_push_back_thrice() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.push_back(1), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 2,
                is_empty: false,
                front: Some(0),
                back: Some(1),
                values: [Some(0), Some(1)]
            }
        );
        assert_eq!(buf.push_back(2), false);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 2,
                is_empty: false,
                front: Some(0),
                back: Some(1),
                values: [Some(0), Some(1)]
            }
        );
    }

    #[test]
    fn n_2_push_back_twice_pop_front_once() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.push_back(1), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 2,
                is_empty: false,
                front: Some(0),
                back: Some(1),
                values: [Some(0), Some(1)]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(1),
                back: Some(1),
                values: [Some(1), None]
            }
        );
    }

    #[test]
    fn n_2_push_back_twice_pop_front_twice() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.push_back(1), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 2,
                is_empty: false,
                front: Some(0),
                back: Some(1),
                values: [Some(0), Some(1)]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(1),
                back: Some(1),
                values: [Some(1), None]
            }
        );
        assert_eq!(buf.pop_front(), Some(1));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
    }

    #[test]
    fn n_2_push_back_twice_pop_front_thrice() {
        let mut buf = CircularBuffer::<i32, 2>::try_new().unwrap();
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.push_back(0), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(0),
                back: Some(0),
                values: [Some(0), None]
            }
        );
        assert_eq!(buf.push_back(1), true);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 2,
                is_empty: false,
                front: Some(0),
                back: Some(1),
                values: [Some(0), Some(1)]
            }
        );
        assert_eq!(buf.pop_front(), Some(0));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 1,
                is_empty: false,
                front: Some(1),
                back: Some(1),
                values: [Some(1), None]
            }
        );
        assert_eq!(buf.pop_front(), Some(1));
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
        assert_eq!(buf.pop_front(), None);
        check!(
            &mut buf,
            Check {
                capacity: 2,
                len: 0,
                is_empty: true,
                front: None,
                back: None,
                values: [None, None]
            }
        );
    }
}
