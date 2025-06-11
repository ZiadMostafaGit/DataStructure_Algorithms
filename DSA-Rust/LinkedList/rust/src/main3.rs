use std::cell::{Ref, RefCell};
use std::io::Cursor;
use std::rc::Rc;
use std::thread::current;

struct Node {
    val: i32,
    next: Option<Rc<RefCell<Node>>>,
}
impl Node {
    fn new(val: i32) -> Self {
        Node { val, next: None }
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
        let node = Rc::new(RefCell::new(Node { val, next: None }));
        if self.head.is_none() {
            self.head = Some(node.clone());
            self.tail = Some(node);
            self.length += 1;
        } else {
            if let Some(ref tail) = self.tail {
                tail.borrow_mut().next = Some(node.clone());
            }
            self.tail = Some(node);
            self.length += 1;
        }
    }

    fn push_front(&mut self, val: i32) {
        let node = Rc::new(RefCell::new(Node { val, next: None }));
        if self.head.is_none() {
            self.head = Some(node.clone());
            self.tail = Some(node);
            self.length += 1;
        } else {
            if let Some(ref head) = self.head {
                node.borrow_mut().next = self.head.clone();
            }

            self.head = Some(node);
            self.length += 1;
        }
    }

    fn pop_back(&mut self) {
        if self.head.is_none() {
            return;
        }
        if let Some(ref head) = self.head.clone() {
            if head.borrow().next.is_none() {
                self.length -= 1;
                self.head = None;
                self.tail = None;
                return;
            }
        }
        let mut current = self.head.clone();
        while let Some(ref node) = current {
            let next_node = node.borrow().next.clone();

            if let Some(ref next) = next_node {
                if next.borrow().next.is_none() {
                    node.borrow_mut().next = None;

                    self.tail = Some(node.clone());
                    self.length -= 1;
                    return;
                }
            }

            current = next_node;
        }
    }

    fn pop_front(&mut self) {
        if self.head.is_none() {
            return;
        }

        if let Some(ref head) = self.head.clone() {
            if head.borrow().next.is_none() {
                self.head = None;
                self.tail = None;
                self.length -= 1;
                return;
            }
        }

        if let Some(ref next) = self.head.clone() {
            self.length -= 1;
            self.head = next.borrow_mut().next.clone();
            return;
        }
    }

    fn swap_head_and_tail(&mut self) {
        let mut current = self.head.clone();
        let temp = self.head.as_ref().unwrap().borrow().next.clone();

        while let Some(ref node) = current.clone() {
            let next_node = node.borrow_mut().next.clone();

            if let Some(ref next) = next_node {
                if next.borrow().next.is_none() {
                    node.borrow_mut().next = self.head.clone();
                    next.borrow_mut().next = temp.clone();
                    let head = self.head.clone().unwrap();
                    self.head = self.tail.clone();
                    self.tail = Some(head);
                    self.tail.as_ref().unwrap().borrow_mut().next = None;
                    break;
                } else {
                    current = node.borrow_mut().next.clone();
                }
            } else {
                return;
            }
        }
    }

    fn left_rotate(&mut self, k: i32) {
        if k <= 0 {
            return;
        }
        let mut iter = k % self.length;

        if iter == 0 {
            return;
        }

        let next = self.tail.as_ref().unwrap().clone();
        next.borrow_mut().next = self.head.clone();

        let mut current = self.head.clone();
        while let Some(ref node) = current.clone() {
            if iter == 1 {
                break;
            }
            iter -= 1;
            current = node.borrow_mut().next.clone();
        }

        self.head = current.as_ref().unwrap().borrow().next.clone();
        self.tail = current.clone();
        if let Some(ref node) = current {
            node.borrow_mut().next = None;
        }
    }

    fn get_n_from_back(&mut self, index: i32) -> Option<i32> {
        if index < 0 || index > self.length {
            return None;
        }
        let iter = self.length.clone() - index;
        let mut current = self.head.clone();
        for _ in 0..iter {
            if let Some(ref node) = current.clone() {
                current = node.borrow().next.clone();
            } else {
                return None;
            }
        }

        current.map(|node| node.borrow().val)
    }

    fn helper(&self, current: Option<Rc<RefCell<Node>>>) {
        if let Some(node) = current {
            self.helper(node.borrow_mut().next.clone());
            println!("{}", node.borrow().val);
        }
    }
    fn print_rev(&self) {
        let current = self.head.clone();
        self.helper(current);
    }

    fn print(&self) {
        let mut current = self.head.clone();
        while let Some(node) = current {
            println!("{}", node.borrow().val);
            current = node.borrow().next.clone();
        }
    }
}

fn main() {
    let mut list = LinkedList::new();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    // list.print();
    // list.push_front(7);

    // list.print();
    // list.swap_head_and_tail();
    // list.left_rotate(10);
    // list.print();
    // list.print_rev();
    // list.print();
    //
    // println!("=======================");
    // let res = list.get_n_from_back(7);
    // match res {
    //     Some(num) => {
    //         println!("{}", num);
    //     }
    //     None => {
    //         println!("Error None");
    //     }
    // }
    // list.pop_back();
    //
    // list.pop_front();
    // list.print();
}
