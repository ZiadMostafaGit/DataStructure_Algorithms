#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

template <typename T> struct Node {
  T data;
  std::shared_ptr<Node<T>> prev;

  Node(T d) : data(d), prev(nullptr) {}
};

template <typename T> class StackLinked {
public:
  std::shared_ptr<Node<T>> head;
  unsigned int size;

  StackLinked() : head(nullptr), size(0) {}

  void push(T the_data) {
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(the_data);
    if (head != nullptr) {
      newNode->prev = head;
    }
    head = newNode;
    size++;
  }

  T pop() {
    if (head == nullptr) {
      throw std::runtime_error("stack is empty");
    }
    T data = head->data;
    head = head->prev;
    size--;
    return data;
  }

  T peek() const {
    if (head == nullptr) {
      throw std::runtime_error("stack is empty");
    }
    return head->data;
  }

  bool isEmpty() const { return head == nullptr; }

  void print() const {
    std::shared_ptr<Node<T>> current = head;
    std::vector<T> temp_vec;
    while (current) {
      temp_vec.push_back(current->data);
      current = current->prev;
    }
    std::reverse(temp_vec.begin(),
                 temp_vec.end());

    for (const T &item : temp_vec) {
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
};

int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  if (op == '^')
    return 3;
  return 0;
}

std::string evaluatePostFix(const std::string &input) {
  std::stack<int> stack;
  for (char val : input) {
    if (isdigit(val)) {
      stack.push(val - '0');
    } else {
      if (stack.size() < 2) {
        throw std::runtime_error("invalid stack operation");
      }
      int val1 = stack.top();
      stack.pop();
      int val2 = stack.top();
      stack.pop();
      int result;
      switch (val) {
      case '+':
        result = val2 + val1;
        break;
      case '-':
        result = val2 - val1;
        break;
      case '*':
        result = val2 * val1;
        break;
      case '/':
        if (val1 == 0)
          throw std::runtime_error("division by zero");
        result = val2 / val1;
        break;
      default:
        throw std::runtime_error("invalid character in input");
      }
      stack.push(result);
    }
  }
  if (stack.size() != 1) {
    throw std::runtime_error("invalid postfix expression");
  }
  return std::to_string(stack.top());
}

std::string fromInfixToPostfix(const std::string &input) {
  std::string output = "";
  std::stack<char> stack;

  for (char c : input) {
    if (isalnum(c)) {
      output += c;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.empty() && stack.top() != '(') {
        output += stack.top();
        stack.pop();
      }
      if (!stack.empty() && stack.top() == '(') {
        stack.pop();
      }
    } else {
      while (!stack.empty() && precedence(stack.top()) >= precedence(c) &&
             stack.top() != '(') {
        output += stack.top();
        stack.pop();
      }
      stack.push(c);
    }
  }

  while (!stack.empty()) {
    output += stack.top();
    stack.pop();
  }
  return output;
}

std::vector<int> asteroidCollision(std::vector<int> &astro) {
  std::vector<int> res;
  std::stack<int> stack;

  for (int val : astro) {
    bool pushed = false;
    while (!stack.empty() && val < 0 && stack.top() > 0) {
      if (std::abs(val) > stack.top()) {
        stack.pop();
      } else if (std::abs(val) == stack.top()) {
        stack.pop();
        pushed = true;
        break;
      } else {
        pushed = true;
        break;
      }
    }
    if (!pushed) {
      stack.push(val);
    }
  }

  while (!stack.empty()) {
    res.push_back(stack.top());
    stack.pop();
  }
  std::reverse(res.begin(), res.end());
  return res;
}

int scoreOfParentheses(const std::string &s) {
  std::stack<int> stack;
  int score = 0;
  for (char c : s) {
    if (c == '(') {
      stack.push(score);
      score = 0;
    } else {
      score = stack.top() + std::max(1, score * 2);
      stack.pop();
    }
  }
  return score;
}

std::vector<int> dailyTemperatures(const std::vector<int> &temperatures) {
  std::stack<int> stack_indices; // Stores indices
  std::vector<int> res(temperatures.size(), 0);

  for (int i = 0; i < temperatures.size(); ++i) {
    while (!stack_indices.empty() &&
           temperatures[i] > temperatures[stack_indices.top()]) {
      int prev_index = stack_indices.top();
      stack_indices.pop();
      res[prev_index] = i - prev_index;
    }
    stack_indices.push(i);
  }
  return res;
}

int main() {
  std::vector<int> arr = {30, 25,20,15, 50, 60};
  std::vector<int> res = dailyTemperatures(arr);
  for (int item : res) {
    std::cout << item << " ";
  }
  std::cout << std::endl;


  StackLinked<int> myStack;
  myStack.push(1);
  myStack.push(2);
  myStack.push(3);
  myStack.print();
  try {
      std::cout << "Popped: " << myStack.pop() << std::endl;
      std::cout << "Peeked: " << myStack.peek() << std::endl;
  } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
  }
  myStack.print();

  std::cout << "Infix to Postfix conversions:" << std::endl;
  try {
      std::cout << "((2+3)*4-(7-5))*(6+3) -> " <<
      fromInfixToPostfix("((2+3)*4-(7-5))*(6+3)") << std::endl; std::cout <<
      "5-9/(3*4/2) -> " << fromInfixToPostfix("5-9/(3*4/2)") << std::endl;
      std::cout << "(1+2)*(6-4) -> " << fromInfixToPostfix("(1+2)*(6-4)") <<
      std::endl; std::cout << "1+2*3-4 -> " << fromInfixToPostfix("1+2*3-4")
      << std::endl; std::cout << "1+2*3 -> " << fromInfixToPostfix("1+2*3")
      << std::endl; std::cout << "2+(3*(4-5*2)*(9/3+6)) -> " <<
      fromInfixToPostfix("2+(3*(4-5*2)*(9/3+6))") << std::endl; std::cout <<
      "a+b*(c^d-e)^(f+G*h)-i -> " <<
      fromInfixToPostfix("a+b*(c^d-e)^(f+G*h)-i") << std::endl;
  } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
  }

  std::cout << "Asteroid Collision:" << std::endl;
  std::vector<int> asteroids = {5, 10, -5};
  std::vector<int> remaining_asteroids = asteroidCollision(asteroids);
  for (int a : remaining_asteroids) {
      std::cout << a << " ";
  }
  std::cout << std::endl;

  std::cout << "Score of Parentheses: \"(()(()))\":" <<
  scoreOfParentheses("(()(()))") << std::endl;

  return 0;
}
//
