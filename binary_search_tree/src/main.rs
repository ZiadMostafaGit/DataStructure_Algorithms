use std::{error, i32, i64, thread::current};

struct Node {
    val: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    fn new(val: i32) -> Self {
        Node {
            val,
            left: None,
            right: None,
        }
    }
}

struct BSA {
    root: Option<Box<Node>>,
}

impl BSA {
    fn new() -> Self {
        BSA { root: None }
    }

    fn is_empty(&self) -> bool {
        self.root.is_none()
    }

    fn insert(&mut self, val: i32) {
        match self.root {
            None => {
                self.root = Some(Box::new(Node::new(val)));
            }
            Some(_) => Self::insert_recursive(&mut self.root, val),
        }
    }

    fn insert_recursive(current: &mut Option<Box<Node>>, val: i32) {
        if let Some(node) = current {
            if val > node.val {
                if node.right.is_some() {
                    Self::insert_recursive(&mut node.right, val);
                } else {
                    node.right = Some(Box::new(Node::new(val)));
                }
            } else if val < node.val {
                if node.left.is_some() {
                    Self::insert_recursive(&mut node.left, val);
                } else {
                    node.left = Some(Box::new(Node::new(val)));
                }
            }
        }
    }

    fn inorder_print(current: &Option<Box<Node>>) {
        if let Some(node) = current {
            Self::inorder_print(&node.left);
            print!("{} ", node.val);
            Self::inorder_print(&node.right);
        }
    }

    fn find(current: &Option<Box<Node>>, ansestor: &mut Vec<i32>, target: i32) -> Option<bool> {
        if let Some(node) = current {
            ansestor.push(node.val);
            if node.val > target {
                return Self::find(&node.left, ansestor, target);
            } else if node.val < target {
                return Self::find(&node.right, ansestor, target);
            } else {
                return Some(true);
            }
        }
        return Some(false);
    }

    // fn delete(&mut self, val: i64) -> Result<bool, i64> {
    //     let mut ansestor: Vec<i64> = Vec::new();
    // }
}

fn main() {
    let mut bst = BSA::new();

    println!("Is BST empty? {}", bst.is_empty());

    let values = [8, 3, 10, 1, 6, 14, 4, 7, 13];
    println!("Inserting values: {:?}", values);
    for &val in &values {
        bst.insert(val);
    }

    println!("Is BST empty after insertion? {}", bst.is_empty());

    println!("Inorder traversal:");
    BSA::inorder_print(&bst.root);

    println!(); // Add a newline at the end

    let mut ansestor: Vec<i32> = Vec::new();
    let is_there = BSA::find(&bst.root, &mut ansestor, 44);

    match is_there {
        Some(val) => println!("the find func return some thing which is {}", val),
        None => println!("the find func return nono which mean we have problem "),
    }
}
