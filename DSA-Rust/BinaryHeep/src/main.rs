struct Heap {
    data: Vec<i32>,
}

impl Heap {
    fn new() -> Self {
        Self { data: Vec::new() }
    }

    fn push(&mut self, val: i32) {
        self.data.push(val);
        self.heapify_up(self.data.len() - 1);
    }

    fn peek(&self) -> Option<i32> {
        self.data.get(0).copied()
    }

    fn pop(&mut self) -> Option<i32> {
        if self.data.is_empty() {
            return None;
        }

        let last = self.data.len() - 1;
        self.data.swap(0, last);
        let min = self.data.pop();

        if !self.data.is_empty() {
            self.heapify_down(0);
        }

        min
    }

    fn heapify_up(&mut self, mut index: usize) {
        while let Some(parent) = Self::parent(index) {
            if self.data[index] < self.data[parent] {
                self.data.swap(index, parent);
                index = parent;
            } else {
                break;
            }
        }
    }

    fn heapify_down(&mut self, mut index: usize) {
        let len = self.data.len();

        loop {
            let left = 2 * index + 1;
            let right = 2 * index + 2;
            let mut smallest = index;

            if left < len && self.data[left] < self.data[smallest] {
                smallest = left;
            }
            if right < len && self.data[right] < self.data[smallest] {
                smallest = right;
            }

            if smallest == index {
                break;
            }

            self.data.swap(index, smallest);
            index = smallest;
        }
    }

    fn parent(index: usize) -> Option<usize> {
        if index == 0 {
            None
        } else {
            Some((index - 1) / 2)
        }
    }
}

fn main() {
    let mut heap = Heap::new();
    heap.push(5);
    heap.push(3);
    heap.push(8);
    heap.push(1);
    heap.push(9);

    println!("Top: {:?}", heap.peek());

    while let Some(val) = heap.pop() {
        println!("Popped: {}", val);
        println!("Top: {:?}", heap.peek());
    }
}
