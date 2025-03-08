use std::cell::RefCell;
use std::collections::VecDeque;
use std::fmt::Display;
use std::rc::Rc;

struct node<T> {
    val: T,
    left: Option<Rc<RefCell<node<T>>>>,
    right: Option<Rc<RefCell<node<T>>>>,
}

impl<T> node<T> {
    fn new(val: T) -> node<T> {
        node {
            val,
            left: None,
            right: None,
        }
    }
}

struct binary_tree<T> {
    root: Option<Rc<RefCell<node<T>>>>,
}

impl<T> binary_tree<T> {
    fn new() -> Self {
        binary_tree { root: None }
    }
    fn is_empty(&mut self) -> bool {
        self.root.is_none()
    }
    fn insert_level_order(&mut self, val: T) {
        let mut new_node = Some(Rc::new(RefCell::new(node::new(val))));
        if self.is_empty() {
            self.root = new_node;
        } else {
            let mut queue: VecDeque<Option<Rc<RefCell<node<T>>>>> = VecDeque::new();
            queue.push_back(self.root.clone());
            while !queue.is_empty() {
                let temp = queue.pop_front().expect("error");
                if let Some(node) = temp.clone() {
                    if node.borrow().left.is_none() {
                        node.borrow_mut().left = new_node;
                        break;
                    } else {
                        queue.push_back(node.borrow().left.clone());
                    }

                    if node.borrow().right.is_none() {
                        node.borrow_mut().right = new_node;
                        break;
                    } else {
                        queue.push_back(node.borrow().right.clone());
                    }
                } else {
                    break;
                }
            }
        }
    }

    fn inorder_recursive(&self, current: Option<Rc<RefCell<node<T>>>>)
    where
        T: Display,
    {
        if let Some(node) = current {
            let node_ref = node.as_ref();

            self.inorder_recursive(node_ref.borrow().left.clone());
            print!("{} ", node_ref.borrow().val);

            self.inorder_recursive(node_ref.borrow().right.clone());
        }
    }
    fn inorder_travirse(&self) -> Result<(), &'static str>
    where
        T: Display,
    {
        if self.root.is_none() {
            Err("tree is empty")
        } else {
            let mut current = self.root.clone();
            self.inorder_recursive(current);
            Ok(())
        }
    }
}

fn main() {
    let mut binary: binary_tree<u32> = binary_tree::new();
    binary.insert_level_order(1);
    binary.insert_level_order(2);
    binary.insert_level_order(3);
    binary.insert_level_order(4);
    binary.insert_level_order(5);
    binary.insert_level_order(6);
    binary.insert_level_order(7);
    match binary.inorder_travirse() {
        Ok(()) => println!(),
        Err(e) => println!("{}", e),
    }
}
