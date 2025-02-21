use std::fmt::Display;

struct Stack<T> {
    data: Vec<T>,
}

impl<T> Stack<T> {
    fn new(capacity: usize) -> Self {
        Stack {
            data: Vec::with_capacity(capacity),
        }
    }

    fn push(&mut self, val: T) {
        self.data.push(val);
    }

    fn pop(&mut self) -> Option<T> {
        self.data.pop()
    }

    fn is_empty(&self) -> bool {
        self.data.is_empty()
    }

    fn peek(&self) -> Option<&T> {
        self.data.last()
    }

    fn print(&self)
    where
        T: Display,
    {
        for item in self.data.iter().rev() {
            print!("{} ", item);
        }
        println!();
    }
}

fn reverse_number(num: i64) -> i64 {
    let mut stack = Stack::new(100);
    let s = num.to_string();
    for c in s.chars() {
        stack.push(c);
    }
    let mut reversed = String::new();
    while let Some(c) = stack.pop() {
        reversed.push(c);
    }
    reversed.parse().unwrap_or(0)
}

fn valid_parentheses(s: &str) -> bool {
    let mut stack = Stack::new(100);
    for c in s.chars() {
        if matches!(c, '(' | '[' | '{') {
            stack.push(c);
        } else if matches!(c, ')' | ']' | '}') {
            stack.pop();
        }
    }
    stack.is_empty()
}

fn reverse_sub_words(s: &mut String) {
    let mut stack = Stack::new(100);
    let mut result = String::new();
    let words = s.split_whitespace().collect::<Vec<&str>>();

    for word in words {
        for c in word.chars() {
            stack.push(c);
        }
        while let Some(c) = stack.pop() {
            result.push(c);
        }
        result.push(' ');
    }

    if !result.is_empty() {
        result.pop();
    }
    *s = result;
}

fn remove_duplicates(s: &str) -> String {
    let mut stack = Stack::new(s.len());
    for c in s.chars() {
        if stack.is_empty() || Some(&c) != stack.peek() {
            stack.push(c);
        } else {
            stack.pop();
        }
    }
    let mut res = String::new();
    while let Some(c) = stack.pop() {
        res.push(c);
    }
    res.chars().rev().collect()
}

fn reverse_parentheses(s: &str) -> String {
    let mut s_chars = s.chars().collect::<Vec<char>>();
    let mut stack = Stack::new(s.len());

    for i in 0..s_chars.len() {
        if s_chars[i] == '(' {
            stack.push(i);
        } else if s_chars[i] == ')' {
            if let Some(start) = stack.pop() {
                let mut start_idx = start + 1;
                let mut end_idx = i - 1;
                while start_idx < end_idx {
                    if matches!(s_chars[start_idx], '(' | ')') {
                        start_idx += 1;
                        continue;
                    }
                    if matches!(s_chars[end_idx], '(' | ')') {
                        end_idx -= 1;
                        continue;
                    }
                    s_chars.swap(start_idx, end_idx);
                    start_idx += 1;
                    end_idx -= 1;
                }
            }
        }
    }

    s_chars
        .iter()
        .filter(|&&c| c.is_ascii_lowercase())
        .collect()
}

fn main() {
    let mut stack = Stack::new(4);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.print();

    println!("{}", valid_parentheses("(()")); // false

    let mut text = String::from("hello world");
    reverse_sub_words(&mut text);
    println!("{}", text); // "olleh dlrow"
}
