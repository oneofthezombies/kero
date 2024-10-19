use std::usize;

struct StackCircularBuffer<const N: usize, T> {
    buf: [T; N],
}

impl<const N: usize, T> StackCircularBuffer<N, T> {
    fn new() -> Self {
        todo!();
    }

    fn capacity(&self) -> usize {
        N
    }

    fn len(&self) -> usize {
        todo!();
    }

    fn is_empty(&self) -> usize {
        todo!();
    }

    fn get(&self, index: usize) -> Option<&T> {
        todo!();
    }

    fn get_mut(&mut self, index: usize) -> Option<&mut T> {
        todo!();
    }

    fn front(&self) -> Option<&T> {
        todo!();
    }

    fn front_mut(&mut self) -> Option<&mut T> {
        todo!();
    }

    fn back(&self) -> Option<&T> {
        todo!();
    }

    fn back_mut(&mut self) -> Option<&mut T> {
        todo!();
    }

    fn pop_front(&mut self) -> Option<T> {
        todo!();
    }

    fn push_back(&mut self, value: T) {
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
