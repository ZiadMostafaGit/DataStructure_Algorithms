use std::cell::{Ref, RefCell};
use std::io::Cursor;
use std::rc::Rc;

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
                    return;
                }
            }

            current = next_node;
        }
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
    println!("Hello, world!");

    let mut list = LinkedList::new();
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    // list.print();
    // list.push_front(7);

    list.print();
    // list.print_rev();
    // list.print();

    list.pop_back();
    list.pop_back();

    list.print();
}
