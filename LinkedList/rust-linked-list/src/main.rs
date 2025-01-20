struct node {
    val: i32,
    next: Option<Box<node>>,
}

impl node {
    fn new(val: i32) -> Self {
        node { val, next: None }
    }
}
struct Linked_list {
    head: Option<Box<node>>,
    tail: Option<*mut node>,
    length: i32,
}
impl Linked_list {
    fn new() -> Self {
        Linked_list {
            head: None,
            tail: None,
            length: 0,
        }
    }

    fn is_empty(&self) -> bool {
        return self.head.is_none() && self.tail.is_none();
    }
    fn push(&mut self, val: i32) {
        let mut new_node = Box::new(node::new(val));
        if self.is_empty() {
            self.head = Some(new_node);
            self.tail = Some(self.head.as_deref().unwrap() as &mut node);
        }
    }
}

fn main() {
    println!("Hello, world!");
}
