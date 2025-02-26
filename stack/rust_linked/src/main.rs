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
    size: u32,
}

impl<T: Display> StackLinked<T> {
    fn new() -> Self {
        StackLinked {
            head: None,
            size: 0,
        }
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
        self.size += 1;
    }

    fn pop(&mut self) -> Result<T, &'static str> {
        if self.head.is_none() {
            Err("stack is embty")
        } else {
            let old_head = self.head.take().unwrap().clone();
            self.head = old_head.borrow().prev.clone();
            self.size -= 1;
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
        let mut mid = 0;
        if self.size >= 2 {
            mid = self.size / 2;
        }
        let mut index = 0;
        while let Some(node) = current.clone().as_ref() {
            if index == mid {
                print!("[{}] ", node.borrow().data.clone());
            } else {
                print!("{} ", node.borrow().data.clone());
            }
            index += 1;
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
        if the_char.is_digit(10) || the_char.is_lowercase() || the_char.is_uppercase() {
            output.push(the_char);
        } else if the_char == '(' {
            stack.push(the_char);
        } else if the_char == '^' {
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

fn asteroid_collision(astro: &mut Vec<i32>) -> Vec<i32> {
    let mut res: Vec<i32> = Vec::with_capacity(astro.len());
    let mut stack: StackLinked<i32> = StackLinked::new();
    for val in astro.iter() {
        if stack.head.is_none() {
            stack.push(*val);
            continue;
        }

        if let Ok(peek) = stack.peek() {
            if peek > 0 && *val < 0 {
                loop {
                    if let Ok(peek) = stack.peek() {
                        if peek.abs() > val.abs() {
                            break;
                        } else if peek.abs() < val.abs() {
                            let _poped = stack.pop();
                        } else if peek.abs() == val.abs() {
                            let _poped = stack.pop();
                            break;
                        }
                    } else {
                        stack.push(*val);
                        break;
                    }
                }
            } else {
                stack.push(*val);
            }
        }
    }

    while let Ok(poped) = stack.pop() {
        res.push(poped);
    }

    res.reverse();
    res
}

fn main() {
    // let mut stack = StackLinked::new();
    let mut arr: Vec<i32> = vec![5, 10, -5];
    let new_arr = asteroid_collision(&mut arr);
    for item in new_arr.iter() {
        print!("{} ", *item);
    }
    println!();
    // stack.push(1);
    // stack.print();
    // stack.push(2);
    // stack.print();
    // stack.push(3);
    // stack.print();
    // stack.push(4);
    // stack.print();
    // stack.push(5);
    // stack.print();
    // stack.push(6);
    // stack.print();
    // stack.push(7);
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

    // let input1 = String::from("((2+3)*4-(7-5))*(6+3)");
    // if let Ok(output1) = from_infix_to_postfix(input1) {
    //     println!("{}", output1);
    // }
    //
    // let input2 = String::from("5-9/(3*4/2)");
    // if let Ok(output2) = from_infix_to_postfix(input2) {
    //     println!("{}", output2);
    // }
    //
    // let input3 = String::from("(1+2)*(6-4)");
    // if let Ok(output3) = from_infix_to_postfix(input3) {
    //     println!("{}", output3);
    // }
    //
    // let input4 = String::from("1+2*3-4");
    // if let Ok(output4) = from_infix_to_postfix(input4) {
    //     println!("{}", output4);
    // }
    //
    // let input5 = String::from("1+2*3");
    // if let Ok(output5) = from_infix_to_postfix(input5) {
    //     println!("{}", output5);
    // }
    //
    // let input5 = String::from("2+(3*(4-5*2)*(9/3+6))");
    // if let Ok(output5) = from_infix_to_postfix(input5) {
    //     println!("{}", output5);
    // }
    //
    // let input5 = String::from("a+b*(c^d-e)^(f+G*h)-i");
    // if let Ok(output5) = from_infix_to_postfix(input5) {
    //     println!("{}", output5);
    // }
}
