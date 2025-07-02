#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

template <typename T> class Stack {
public:
  std::vector<T> data;
  unsigned int size;

  Stack(size_t capacity) : data(), size(0) { data.reserve(capacity); }

  void push(T val) {
    data.push_back(val);
    size++;
  }

  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty, cannot pop.");
    }
    size--;
    T val = data.back();
    data.pop_back();
    return val;
  }

  bool isEmpty() const { return data.empty(); }

  const T &top() const {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty, cannot peek.");
    }
    return data.back();
  }

  void print() const {
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

  void insertAtBottom(T val) {
    data.insert(data.begin(), val);
    size++;
  }
};

long long reverseNumber(long long num) {
  std::stack<char> charStack;
  std::string s = std::to_string(num);
  for (char c : s) {
    charStack.push(c);
  }
  std::string reversed_str;
  while (!charStack.empty()) {
    reversed_str += charStack.top();
    charStack.pop();
  }
  try {
    return std::stoll(reversed_str);
  } catch (const std::exception &e) {
    return 0;
  }
}

bool isValidParentheses(const std::string &s) {
  std::stack<char> charStack;
  for (char c : s) {
    if (c == '(' || c == '[' || c == '{') {
      charStack.push(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (charStack.empty()) {
        return false;
      }
      char topChar = charStack.top();
      charStack.pop();
      if ((c == ')' && topChar != '(') || (c == ']' && topChar != '[') ||
          (c == '}' && topChar != '{')) {
        return false;
      }
    }
  }
  return charStack.empty();
}

void reverseSubWords(std::string &s) {
  std::string result = "";
  std::stack<char> charStack;
  std::string current_word;

  for (char c : s) {
    if (c == ' ') {
      while (!charStack.empty()) {
        result += charStack.top();
        charStack.pop();
      }
      result += ' ';
    } else {
      charStack.push(c);
    }
  }
  // Handle the last word
  while (!charStack.empty()) {
    result += charStack.top();
    charStack.pop();
  }
  s = result;
}

std::string removeDuplicates(const std::string &s) {
  std::stack<char> charStack;
  for (char c : s) {
    if (charStack.empty() || charStack.top() != c) {
      charStack.push(c);
    } else {
      charStack.pop();
    }
  }
  std::string res;
  while (!charStack.empty()) {
    res += charStack.top();
    charStack.pop();
  }
  std::reverse(res.begin(), res.end());
  return res;
}

std::string reverseParentheses(const std::string &s) {
  std::string res = s;
  Stack<int> open_paren_indices = Stack<int>(s.size());

  for (int i = 0; i < res.length(); ++i) {
    if (res[i] == '(') {
      open_paren_indices.push(i);
    } else if (res[i] == ')') {
      if (!open_paren_indices.isEmpty()) {
        int start_index = open_paren_indices.top();
        open_paren_indices.pop();
        std::reverse(res.begin() + start_index + 1, res.begin() + i);
      }
    }
  }

  std::string filtered_res = "";
  for (char c : res) {
    if (c != '(' && c != ')') {
      filtered_res += c;
    }
  }
  return filtered_res;
}

int main() {
  Stack<int> myStack(4);
  myStack.push(1);
  myStack.push(2);
  myStack.push(3);
  myStack.push(4);
  myStack.push(5);
  std::cout << "Initial stack: ";
  myStack.print();

  myStack.insertAtBottom(6);
  std::cout << "Stack after insertAtBottom(6): ";
  myStack.print();

  std::cout << "Valid parentheses \"(()\": "
            << (isValidParentheses("(()") ? "true" : "false") << std::endl;
  std::cout << "Valid parentheses \"()[]{}\": "
            << (isValidParentheses("()[]{}") ? "true" : "false") << std::endl;

  std::string text = "hello world";
  reverseSubWords(text);
  std::cout << "Reverse sub-words \"hello world\": \"" << text << "\""
            << std::endl;

  std::cout << "Remove duplicates \"azxxzy\": " << removeDuplicates("azxxzy")
            << std::endl;

  std::cout << "Reverse parentheses \"(abcd)\": "
            << reverseParentheses("(abcd)") << std::endl;
  std::cout << "Reverse parentheses \"(u(love)i)\": "
            << reverseParentheses("(u(love)i)") << std::endl;
  std::cout << "Reverse parentheses \"(ed(et(oc))el)\": "
            << reverseParentheses("(ed(et(oc))el)") << std::endl;

  return 0;
}
