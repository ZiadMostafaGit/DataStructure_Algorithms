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
        let mut current = self.root.as_mut();

        let mut index = 0;

        for c in word.chars() {
            index = char_to_index(c);
            if current.child[index].is_none() {
                current.child[index] = Some(Box::new(Node::new()));
            }
            current = current.child[index].as_mut().unwrap();
        }
    }

    fn search(&mut self, word: String) -> bool {
        let mut current = self.root.as_mut();
        let mut index = 0;
        for c in word.chars() {
            index = char_to_index(c);
            if current.child[index].is_none() {
                return false;
            }
            current = current.child[index].as_mut().unwrap();
        }
        return true;
    }
}

fn char_to_index(c: char) -> usize {
    (c as u8 - b'a') as usize
}

fn main() {
    println!("Hello, world!");
    let mut t1 = Trie::new();
    t1.insert("hello".to_string());
    t1.insert("my".to_string());
    t1.insert("name".to_string());
    t1.insert("is".to_string());
    t1.insert("ziad".to_string());
    let mut res: bool = false;

    res = t1.search("hi".to_string());
    println!("{}", res);
    res = t1.search("zizo".to_string());
    println!("{}", res);
    res = t1.search("ziad".to_string());
    println!("{}", res);
    res = t1.search("hello".to_string());
    println!("{}", res);
    res = t1.search("nello".to_string());
    println!("{}", res);
}
