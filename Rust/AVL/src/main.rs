use std::cmp::max;
struct Node {
    val: i32,
    height: i32,
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    fn new(val: i32) -> Self {
        Node {
            val,
            height: 0,
            left: None,
            right: None,
        }
    }

    fn get_height(&self, node: &Option<Box<Node>>) -> i32 {
        match node {
            Some(n) => n.height,
            None => -1,
        }
    }

    fn update_height(&mut self) {
        self.height = 1 + max(self.get_height(&self.left), self.get_height(&self.right));
    }

    fn balance_factor(&self) -> i32 {
        return self.get_height(&self.left) - self.get_height(&self.right);
    }
}

struct AVL {
    root: Option<Box<Node>>,
}

impl AVL {
    fn new() -> Self {
        AVL { root: None }
    }


    fn insert()





}

fn main() {
    println!("Hello, world!");
}
