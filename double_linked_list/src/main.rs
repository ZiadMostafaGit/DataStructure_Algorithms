use std::cell::RefCell;
use std::mem;
use std::rc::{Rc, Weak};

struct Node {
    val: i32,
    next: Option<Rc<RefCell<Node>>>,
    prev: Option<Weak<RefCell<Node>>>, // Use Weak to avoid reference cycles
}

impl Node {
    fn new(val: i32) -> Self {
        Node {
            val,
            next: None,
            prev: None,
        }
    }
}

struct LinkedList {
    head: Option<Rc<RefCell<Node>>>,
    tail: Option<Rc<RefCell<Node>>>,
    length: i32,
}

impl LinkedList {
    fn new() -> Self {
        LinkedList {
            head: None,
            tail: None,
            length: 0,
        }
    }

    fn push_back(&mut self, val: i32) {
        let new_node = Rc::new(RefCell::new(Node::new(val)));
        if self.head.is_none() {
            self.head = Some(new_node.clone());
            self.tail = Some(new_node);
        } else {
            if let Some(tail) = &self.tail {
                new_node.borrow_mut().prev = Some(Rc::downgrade(tail));
                tail.borrow_mut().next = Some(new_node.clone());
            }
            self.tail = Some(new_node);
        }
        self.length += 1;
    }

    fn push_front(&mut self, val: i32) {
        let new_node = Rc::new(RefCell::new(Node::new(val)));
        if self.head.is_none() {
            self.head = Some(new_node.clone());
            self.tail = Some(new_node);
        } else {
            if let Some(head) = &self.head {
                head.borrow_mut().prev = Some(Rc::downgrade(&new_node));
                new_node.borrow_mut().next = Some(head.clone());
            }
            self.head = Some(new_node);
        }
        self.length += 1;
    }

    fn pop_back(&mut self) {
        if self.head.is_none() {
            return;
        }

        if let Some(tail) = self.tail.clone() {
            if let Some(prev_weak) = &tail.borrow().prev {
                if let Some(prev) = prev_weak.upgrade() {
                    prev.borrow_mut().next = None;
                    self.tail = Some(prev);
                }
            } else {
                self.head = None;
                self.tail = None;
            }
            self.length -= 1;
        }
    }

    fn pop_front(&mut self) {
        if self.head.is_none() {
            return;
        }

        if let Some(head) = self.head.clone() {
            if let Some(next) = &head.borrow().next {
                next.borrow_mut().prev = None;
                self.head = Some(next.clone());
            } else {
                self.head = None;
                self.tail = None;
            }
            self.length -= 1;
        }
    }

    fn insert(&mut self, index: i32, val: i32) {
        if index < 0 || index > self.length {
            return;
        }

        if index == 0 {
            self.push_front(val);
        } else if index == self.length {
            self.push_back(val);
        } else {
            let new_node = Rc::new(RefCell::new(Node::new(val)));
            let mut current = self.head.clone();
            for _ in 0..(index - 1) {
                if let Some(node) = current {
                    current = node.borrow().next.clone();
                }
            }

            if let Some(current_node) = current {
                let next_node = current_node.borrow().next.clone();
                new_node.borrow_mut().prev = Some(Rc::downgrade(&current_node));
                new_node.borrow_mut().next = next_node.clone();
                if let Some(next) = next_node {
                    next.borrow_mut().prev = Some(Rc::downgrade(&new_node));
                }
                current_node.borrow_mut().next = Some(new_node);
                self.length += 1;
            }
        }
    }

    fn search(&self, val: i32) -> Option<i32> {
        let mut current = self.head.clone();
        let mut index = 0;
        while let Some(node) = current {
            if node.borrow().val == val {
                return Some(index);
            }
            current = node.borrow().next.clone();
            index += 1;
        }
        None
    }

    fn print_forward(&self) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            print!("{} ", node.borrow().val);
            current = node.borrow().next.clone();
        }
        println!();
    }

    fn print_backward(&self) {
        let mut current = self.tail.clone();
        while let Some(node) = current {
            print!("{} ", node.borrow().val);
            current = node.borrow().prev.as_ref().and_then(|w| w.upgrade());
        }
        println!();
    }

    fn find_mid(&mut self) -> Option<i32> {
        let mut slow = self.head.clone();
        let mut fast = self.head.clone();

        while let (Some(fast_node), Some(next_fast)) =
            (fast.clone(), fast.clone().unwrap().borrow().next.clone())
        {
            if let Some(last_next) = next_fast.borrow().next.clone() {
                slow = slow.unwrap().borrow().next.clone();
                fast = next_fast.borrow().next.clone();
            } else {
                break;
            }
        }
        slow.map(|node| node.borrow().val)
    }

    fn swap_kth(&mut self, k: i32) {
        if k <= 0 || k > self.length {
            return;
        }
        if 2 * k - 1 == self.length {
            return;
        }

        let mut left = self.head.clone();
        for _ in 1..k {
            if let Some(ref node) = left.clone() {
                left = node.borrow().next.clone();
            }
        }

        let mut right = self.tail.clone();
        for _ in 1..k {
            if let Some(ref node) = right.clone() {
                right = node.borrow().prev.as_ref().and_then(|weak| weak.upgrade());
            }
        }

        let left_node = match left {
            Some(ref node) => node.clone(),
            None => return,
        };
        let right_node = match right {
            Some(ref node) => node.clone(),
            None => return,
        };

        if Rc::ptr_eq(&left_node, &right_node) {
            return;
        }

        if let Some(ref left_next) = left_node.borrow().next {
            if Rc::ptr_eq(left_next, &right_node) {
                let left_prev = left_node.borrow().prev.as_ref().and_then(|w| w.upgrade());
                let right_next = right_node.borrow().next.clone();

                if let Some(ref lp) = left_prev {
                    lp.borrow_mut().next = Some(right_node.clone());
                } else {
                    self.head = Some(right_node.clone());
                }

                if let Some(ref rn) = right_next {
                    rn.borrow_mut().prev = Some(Rc::downgrade(&left_node));
                } else {
                    self.tail = Some(left_node.clone());
                }

                {
                    let mut left_borrow = left_node.borrow_mut();
                    let mut right_borrow = right_node.borrow_mut();
                    left_borrow.next = right_next;
                    right_borrow.prev = left_prev.map(|n| Rc::downgrade(&n));
                    right_borrow.next = Some(left_node.clone());
                    left_borrow.prev = Some(Rc::downgrade(&right_node));
                }
                return;
            }
        }

        let left_prev = left_node.borrow().prev.as_ref().and_then(|w| w.upgrade());
        let left_next = left_node.borrow().next.clone();
        let right_prev = right_node.borrow().prev.as_ref().and_then(|w| w.upgrade());
        let right_next = right_node.borrow().next.clone();

        if let Some(ref lp) = left_prev {
            lp.borrow_mut().next = Some(right_node.clone());
        } else {
            self.head = Some(right_node.clone());
        }
        if let Some(ref ln) = left_next {
            ln.borrow_mut().prev = Some(Rc::downgrade(&right_node));
        } else {
            self.tail = Some(right_node.clone());
        }

        if let Some(ref rp) = right_prev {
            rp.borrow_mut().next = Some(left_node.clone());
        } else {
            self.head = Some(left_node.clone());
        }
        if let Some(ref rn) = right_next {
            rn.borrow_mut().prev = Some(Rc::downgrade(&left_node));
        } else {
            self.tail = Some(left_node.clone());
        }

        {
            let mut left_borrow = left_node.borrow_mut();
            let mut right_borrow = right_node.borrow_mut();
            std::mem::swap(&mut left_borrow.prev, &mut right_borrow.prev);
            std::mem::swap(&mut left_borrow.next, &mut right_borrow.next);
        }
    }

    fn reverse(&mut self) {
        let mut current = self.tail.clone();

        if self.head.is_none() || self.length < 2 {
            return;
        }
        while let Some(node) = current.clone() {
            let temp = node.borrow().next.clone();
            let prev = node.borrow().prev.as_ref().and_then(|w| w.upgrade());
            node.borrow_mut().next = prev;
            node.borrow_mut().prev = temp.as_ref().map(Rc::downgrade);
            current = node.borrow_mut().next.clone();
        }
        mem::swap(&mut self.head, &mut self.tail);
    }
}
fn main() {
    let mut list = LinkedList::new();

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(5);
    list.push_back(1);
    list.push_back(200);
    list.push_front(0);

    // println!("List forward:");
    // list.print_forward(); // Expected: 1 5 10 20 30
    //
    // println!("List backward:");
    // list.print_backward(); // Expected: 30 20 10 5 1
    //
    // // Remove elements
    // list.pop_front();
    // list.pop_back();
    //
    // println!("After popping front and back:");
    // list.print_forward(); // Expected: 5 10 20
    //
    // // Insert at index
    // list.insert(1, 15);
    // println!("After inserting 15 at index 1:");
    // list.print_forward(); // Expected: 5 15 10 20
    //
    // // Search for a value
    // if let Some(index) = list.search(10) {
    //     println!("Value 10 found at index: {}", index);
    // } else {
    //     println!("Value 10 not found.");
    // }
    //
    // // Find the middle element
    // if let Some(mid) = list.find_mid() {
    //     println!("Middle element: {}", mid);
    // } else {
    //     println!("List is empty.");
    // }
    //
    // Swap kth elements
    // list.swap_kth(2);
    // println!("After swapping 2nd element from both ends:");
    list.print_forward();
    list.print_backward();
    list.reverse();
    list.print_forward();
}
