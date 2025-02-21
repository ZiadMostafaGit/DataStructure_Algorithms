#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T> class Stack {
private:
  unique_ptr<T[]> arr;
  int top;
  size_t cap;

public:
  Stack(size_t size) : arr(make_unique<T[]>(size)), top(-1), cap(size) {
    for (size_t i = 0; i < size; ++i)
      arr[i] = T();
  }

  void resize() {
    size_t new_cap = cap * 2;
    unique_ptr<T[]> new_arr = make_unique<T[]>(new_cap);

    // Initialize new array with defaults
    for (size_t i = 0; i < new_cap; ++i)
      new_arr[i] = T();

    // Copy existing elements
    for (int i = 0; i <= top; ++i)
      new_arr[i] = arr[i];

    arr = move(new_arr);
    cap = new_cap;
  }

  void push(T val) {
    if (top == static_cast<int>(cap) - 1)
      resize();
    arr[++top] = val;
  }

  bool is_empty() const { return top == -1; }

  T pop() {
    if (is_empty())
      throw runtime_error("Stack is empty");
    return arr[top--];
  }

  T peek() const {
    if (is_empty())
      throw runtime_error("stack is empty");
    return arr[top];
  }

  void print() const {
    for (int i = top; i >= 0; --i)
      cout << arr[i] << " ";
    cout << "\n";
  }

  int64_t reverse_number(int64_t num) {
    string str = to_string(num);
    Stack<char> stack(100);

    for (char c : str)
      stack.push(c);

    string reversed;
    while (!stack.is_empty())
      reversed += stack.pop();

    return stoll(reversed);
  }

  bool valid_parentheses(const string &s) {
    Stack<char> stack(100);
    for (char c : s) {
      if (c == '(' || c == '[' || c == '{') {
        stack.push(c);
      } else if (c == ')' || c == ']' || c == '}') {
        try {
          stack.pop();
        } catch (...) { /* ignore empty stack */
        }
      }
    }
    return stack.is_empty();
  }

  void reverse_sub_words(string &s) {
    Stack<char> stack(100);
    string result;
    istringstream iss(s);
    string word;

    while (iss >> word) {
      for (char c : word)
        stack.push(c);
      while (!stack.is_empty())
        result += stack.pop();
      result += " ";
    }

    if (!result.empty())
      result.pop_back();
    s = result;
  }

  string removeDuplicates(string s) {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
      if (st.empty() || s[i] != st.top()) {
        st.push(s[i]);

      } else {
        st.pop();
      }
    }
    string res = "";
    while (!st.empty()) {
      res += st.top();
      st.pop();
    }

    char temp = 'a';
    int index = res.size() - 1;
    for (int i = 0; i < res.size() / 2; i++) {
      temp = res[i];
      res[i] = res[index];
      res[index] = temp;
      index--;
    }

    return res;
  }

  string reverseParentheses(string s) {

    stack<int> st;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        st.push(i);
      }
      if (s[i] == ')') {
        int index = st.top() + 1;
        st.pop();
        char temp = 'a';
        int j = i - 1;
        while (index < j) {
          if (s[index] == '(' || s[index] == ')') {
            index++;
            continue;
          }
          if (s[j] == '(' || s[j] == ')') {
            j--;
            continue;
          }
          temp = s[index];
          s[index] = s[j];
          s[j] = temp;
          index++;
          j--;
        }
      }
    }
    string new_s = "";
    for (int i = 0; i < s.size(); i++) {
      if (s[i] >= 97 && s[i] <= 122) {
        new_s += s[i];
      }
    }
    return new_s;
  }
};

int main() {
  Stack<int> stack(4);
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  stack.push(5);
  stack.print();

  // Test parentheses validation
  cout << boolalpha << stack.valid_parentheses("(()") << "\n"; // false

  // Test word reversal
  string text = "hello world";
  stack.reverse_sub_words(text);
  cout << text << "\n"; // "olleh dlrow"

  return 0;
}
