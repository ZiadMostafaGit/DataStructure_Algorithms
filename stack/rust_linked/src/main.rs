use std::cell::RefCell;
use std::error::Error;
use std::fmt::Display;
use std::rc::Rc;

struct Node<T> {
    data: T,
    prev: Option<Rc<RefCell<Node<T>>>>,
}

impl<T> Node<T> {
    fn new(the_data: T) -> Self {
        Node {
            data: the_data,
            prev: None,
        }
    }
}

struct StackLinked<T: Display> {
    head: Option<Rc<RefCell<Node<T>>>>,
}

impl<T: Display> StackLinked<T> {
    fn new() -> Self {
        StackLinked { head: None }
    }

    fn push(&mut self, the_data: T) {
        let new_node = Rc::new(RefCell::new(Node::new(the_data)));

        match self.head.take() {
            Some(old_head) => {
                new_node.borrow_mut().prev = Some(old_head.clone());
                self.head = Some(new_node);
            }
            None => {
                self.head = Some(new_node);
            }
        }
    }

    fn pop(&mut self) -> Result<T, &'static str> {
        if self.head.is_none() {
            Err("stack is embty")
        } else {
            let old_head = self.head.take().unwrap().clone();
            self.head = old_head.borrow().prev.clone();
            Ok(Rc::try_unwrap(old_head).ok().unwrap().into_inner().data)
        }
    }

    fn peek(&self) -> Result<T, &'static str>
    where
        T: Clone,
    {
        if let Some(node) = self.head.as_ref() {
            Ok(node.borrow().data.clone())
        } else {
            Err("stack is embty")
        }
    }

    fn print(&self)
    where
        T: Clone,
    {
        let mut current = self.head.clone();
        while let Some(node) = current.clone().as_ref() {
            print!("{} ", node.borrow().data.clone());
            current = node.borrow().prev.clone();
        }
        println!();
    }
}

fn evaluate_post_fix(input: String) -> Result<String, &'static str> {
    let mut stack: StackLinked<i32> = StackLinked::new();
    let mut output = String::new();

    for val in input.chars() {
        if val.is_digit(10) {
            stack.push(val.to_digit(10).unwrap() as i32);
        } else {
            let val1 = stack.pop();
            let val2 = stack.pop();

            match (val1, val2) {
                (Ok(v1), Ok(v2)) => {
                    let result = match val {
                        '+' => v2 + v1,
                        '-' => v2 - v1,
                        '*' => v2 * v1,
                        '/' => {
                            if v1 == 0 {
                                return Err("division by zero");
                            }
                            v2 / v1
                        }
                        _ => return Err("invalid character in input"),
                    };
                    stack.push(result);
                }
                _ => return Err("invalid stack operation"),
            }
        }
    }

    if let Ok(result) = stack.pop() {
        output = result.to_string();
    }

    Ok(output)
}

fn from_infix_to_postfix(input: String) -> Result<String, &'static str> {
    let mut stack: StackLinked<char> = StackLinked::new();
    let mut output = String::new();
    for the_char in input.chars() {
        if the_char.is_digit(10) {
            output.push(the_char);
        } else if the_char == '(' {
            stack.push(the_char);
        } else if the_char == ')' {
            while let Ok(poped) = stack.pop() {
                output.push(poped);
                if let Ok(peek) = stack.peek() {
                    if peek == '(' {
                        let _ = stack.pop();
                        break;
                    }
                }
            }
        } else {
            if stack.head.is_none() {
                stack.push(the_char);
            } else {
                if let Ok(peek) = stack.peek() {
                    if peek == '('
                        || ((the_char == '*' || the_char == '/') && (peek == '-' || peek == '+'))
                    {
                        stack.push(the_char);
                    } else {
                        loop {
                            if let Ok(val) = stack.pop() {
                                output.push(val);
                            }

                            if let Ok(peek) = stack.peek() {
                                if stack.head.is_none() || peek == '(' {
                                    stack.push(the_char);
                                    break;
                                }
                            } else {
                                stack.push(the_char);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    while let Ok(poped) = stack.pop() {
        output.push(poped);
    }

    Ok(output)
}

fn main() {
    let mut stack = StackLinked::new();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);
    // stack.print();
    // let poped = stack.pop();
    // match poped {
    //     Ok(val) => println!("the value poped form stack is {}", val),
    //     Err(e) => println!("{}", e),
    // }
    //
    // let poped = stack.pop();
    // match poped {
    //     Ok(val) => println!("the value poped form stack is {}", val),
    //     Err(e) => println!("{}", e),
    // }
    //
    // let poped = stack.pop();
    // match poped {
    //     Ok(val) => println!("the value poped form stack is {}", val),
    //     Err(e) => println!("{}", e),
    // }
    //
    // stack.print();
    // stack.push(2003);
    //
    // stack.print();

    let input1 = String::from("((2+3)*4-(7-5))*(6+3)");
    if let Ok(output1) = from_infix_to_postfix(input1) {
        println!("{}", output1);
    }

    let input2 = String::from("5-9/(3*4/2)");
    if let Ok(output2) = from_infix_to_postfix(input2) {
        println!("{}", output2);
    }

    let input3 = String::from("(1+2)*(6-4)");
    if let Ok(output3) = from_infix_to_postfix(input3) {
        println!("{}", output3);
    }

    let input4 = String::from("1+2*3-4");
    if let Ok(output4) = from_infix_to_postfix(input4) {
        println!("{}", output4);
    }

    let input5 = String::from("1+2*3");
    if let Ok(output5) = from_infix_to_postfix(input5) {
        println!("{}", output5);
    }

    let input5 = String::from("2+(3*(4-5*2)*(9/3+6))");
    if let Ok(output5) = from_infix_to_postfix(input5) {
        println!("{}", output5);
    }
}
