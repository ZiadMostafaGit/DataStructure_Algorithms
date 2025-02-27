#include "stack.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

template <typename T> stack<T>::stack(int sz) {
  arr = make_unique<T[]>(sz);
  top = -1;
  size = sz;
}

template <typename T> bool stack<T>::is_full() { return size == top + 1; }

template <typename T> bool stack<T>::is_empty() { return top == -1; }

template <typename T> void stack<T>::push(T val) {
  if (is_full()) {
    resize();
  }
  top++;
  arr[top] = val;
}

template <typename T> int stack<T>::get_top() { return top; }

template <typename T> void stack<T>::resize() {
  unique_ptr<T[]> new_arr = make_unique<T[]>(size * 2);
  for (int i = 0; i < size; i++)
    new_arr[i] = arr[i];
  size = size * 2;
  arr = move(new_arr);
}

template <typename T> void stack<T>::pop() {
  if (is_empty()) {
    cout << "the stack is empty...!\n";
    return;
  }
  top--;
}

template <typename T> int stack<T>::pick() {
  if (is_empty()) {
    cout << "the stack is empty...!\n";
    return 0;
  }
  return arr[top];
}

template <typename T> void stack<T>::print() {
  if (is_empty()) {
    cout << "there are no elements to print..!\n";
    return;
  }
  for (int i = top; i >= 0; i--)
    cout << arr[i] << " ";

  cout << endl;
}

template <typename T> void stack<T>::deletestack() { top = -1; }

template <typename T> void stack<T>::reverse() {
  int j = 0;
  int i = top;
  while (i >= j) {
    int temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
    j++;
    i--;
  }
}

template <typename T> bool stack<T>::Valid_Parentheses(string s) {
  int sz = s.length();
  int t = 0;
  for (int i = 0; i < sz; i++) {
    if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
      push(s[i]);
      t++;
    } else if (!is_empty() && ((s[i] == ')' && arr[top] == '(') ||
                               (s[i] == '}' && arr[top] == '{') ||
                               (s[i] == ']' && arr[top] == '['))) {
      pop();
      t--;
    } else {
      return false;
    }
  }
  return is_empty();
}

template <typename T>
string stack<T>::RemoveAllAdjacentDuplicatesInString(string s) {
  int sz = s.length();
  for (int i = 0; i < sz; i++) {
    if (is_empty()) {
      push(s[i]);
      continue;
    }
    if (s[i] == arr[top]) {
      pop();
    } else {
      push(s[i]);
    }
  }
  string newstring(top + 1, '\0');
  for (int i = 0; i <= top; i++) {
    newstring[i] = arr[i];
  }
  return newstring;
}

template <typename T> void stack<T>::printfront() {
  for (int i = 0; i <= top; i++)
    cout << arr[i] << " ";
  cout << endl;
}

template <typename T> void stack<T>::insert_at_bottom(int val, int pos) {
  if (pos == -1) {
    arr[0] = val;
    top++;
    return;
  }
  arr[pos + 1] = arr[pos];
  return insert_at_bottom(val, pos - 1);
}
template <typename T>
vector<int> stack<T>::Asteroid_Collision(vector<int> &asteroids) {
  vector<int> stack;

  int top = -1;
  bool flag = true;
  for (int i = 0; i < asteroids.size(); i++) {
    if (stack.empty()) {
      stack.push_back(asteroids[i]);
      top++;
    } else {
      if (stack[top] > 0 && asteroids[i] < 0) {
        while (!stack.empty() && stack[top] > 0) {
          if (abs(stack[top]) > abs(asteroids[i])) {
            flag = false;
            break;
          } else if (abs(stack[top]) < abs(asteroids[i])) {
            stack.pop_back();
            top--;
          } else if (abs(stack[top]) == abs(asteroids[i])) {
            stack.pop_back();
            top--;
            flag = false;
            break;
          }
        }
        if (flag) {
          stack.push_back(asteroids[i]);
          top++;
        }
      } else {
        stack.push_back(asteroids[i]);
        top++;
      }
    }
  }
  return stack;
}
template <typename T> int stack<T>::Score_of_Parentheses(string s) {
  int score = 0;
  for (char c : s) {
    if (c == '(') {
      push(score);
      score = 0;
    } else {
      score = max(2 * score, 1) + pick();
      pop();
    }
  }
  return score;
}
