use std::thread::current;

struct Node {
    is_leaf: bool,

    child: [Option<Box<Node>>; 26],
}

impl Node {
    fn new() -> Self {
        Node {
            is_leaf: false,
            child: std::array::from_fn(|_| None),
        }
    }
}

struct Trie {
    root: Box<Node>,
}

impl Trie {
    fn new() -> Self {
        Trie {
            root: Box::new(Node::new()),
        }
    }
    fn insert(&mut self, word: String) {
        let mut current = self.root.as_mut().unwrap();

        for c in word.chars() {
            let index = self.char_to_index(c);

            // Get or insert the child node
            current = current.child[index]
                .get_or_insert_with(|| Box::new(Node::new()))
                .as_mut();
        }

        current.is_leaf = true;
    }

    fn char_to_index(&self, c: char) -> usize {
        (c as u8 - b'a') as usize
    }
}

fn main() {
    println!("Hello, world!");
}
