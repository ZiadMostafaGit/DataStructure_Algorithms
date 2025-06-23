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

    fn delete(&mut self, val: i32) {
        delete_node(&mut self.root, val);
    }
}

fn delete_node(node: &mut Option<Box<Node>>, val: i32) {
    if let Some(n) = node {
        if n.val > val {
            delete_node(&mut n.left, val);
        } else if n.val < val {
            delete_node(&mut n.right, val);
        } else {
            match (n.left.take(), n.right.take()) {
                (None, None) => *node = None,
                (Some(left), None) => *node = Some(left),
                (None, Some(right)) => *node = Some(right),
                (Some(left), Some(right)) => {
                    let min_val = find_min(&right);
                    n.val = min_val;
                    n.left = Some(left);
                    n.right = Some(right);
                    delete_node(&mut n.right, min_val);
                }
            }
        }
    }
}

fn find_min(mut node: &Box<Node>) -> i32 {
    while let Some(ref left) = node.left {
        node = left;
    }
    node.val
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

    println!("Inorder traversal after insertion:");
    BSA::inorder_print(&bst.root);
    println!();

    // Now test delete
    let to_delete = [3, 10, 8]; // delete a node with two children, one child, then root
    for &val in &to_delete {
        println!("\nDeleting value: {}", val);
        bst.delete(val);
        println!("Inorder traversal after deleting {}:", val);
        BSA::inorder_print(&bst.root);
        println!();
    }
}
