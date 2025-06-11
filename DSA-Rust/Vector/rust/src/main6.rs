use std::fmt;

struct Array {
    arr: Box<[i32]>,
    size: usize,
    capacity: usize,
}

impl Array {
    fn new(capa: usize) -> Self {
        Array {
            arr: vec![0; capa].into_boxed_slice(),
            size: 0,
            capacity: capa,
        }
    }

    fn double_capacity(&mut self) {
        self.capacity *= 2;
        let mut new_arr = vec![0; self.capacity].into_boxed_slice();
        new_arr[..self.size].copy_from_slice(&self.arr[..self.size]);
        self.arr = new_arr;
    }

    fn push_back(&mut self, num: i32) {
        if self.size == self.capacity {
            self.double_capacity();
        }
        self.arr[self.size] = num;
        self.size += 1;
    }

    fn pop(&mut self) -> Result<(), &'static str> {
        if self.size == 0 {
            return Err("array is empty");
        }
        self.size -= 1;
        Ok(())
    }

    fn insert(&mut self, idx: usize, val: i32) -> Result<(), &'static str> {
        if idx > self.size {
            return Err("index out of range");
        }

        if self.size == self.capacity {
            self.double_capacity();
        }

        for i in (idx..self.size).rev() {
            self.arr[i + 1] = self.arr[i];
        }
        self.arr[idx] = val;
        self.size += 1;
        Ok(())
    }

    fn print(&self) {
        println!("{:?}", &self.arr[..self.size]);
    }

    fn right_rotation(&mut self) {
        if self.size == 0 {
            return;
        }

        let last_index = self.arr[self.size - 1];
        for i in (1..self.size).rev() {
            self.arr[i] = self.arr[i - 1];
        }
        self.arr[0] = last_index;
    }

    fn left_rotation(&mut self) {
        if self.size == 0 {
            return;
        }

        let first_index = self.arr[0];
        for i in 0..(self.size - 1) {
            self.arr[i] = self.arr[i + 1];
        }
        self.arr[self.size - 1] = first_index;
    }

    fn right_rotation_with_steps(&mut self, mut num: usize) {
        if self.size == 0 {
            return;
        }

        num %= self.size;
        for _ in 0..num {
            self.right_rotation();
        }
    }

    fn delete_position(&mut self, idx: usize) -> Result<i32, &'static str> {
        if idx >= self.size {
            return Err("index out of range");
        }

        let deleted = self.arr[idx];
        for i in idx..(self.size - 1) {
            self.arr[i] = self.arr[i + 1];
        }
        self.size -= 1;
        Ok(deleted)
    }

    fn improved_search(&mut self, num: i32) -> isize {
        for i in 0..self.size {
            if self.arr[i] == num {
                if i > 0 {
                    self.arr.swap(i, i - 1);
                }
                return i as isize;
            }
        }
        -1
    }
}

// impl fmt::Debug for Array {
//     fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
//         write!(f, "{:?}", &self.arr[..self.size])
//     }
// }

fn main() {
    let mut arr = Array::new(5);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.print();
    arr.right_rotation();
    arr.print();
    arr.left_rotation();
    arr.print();
}
