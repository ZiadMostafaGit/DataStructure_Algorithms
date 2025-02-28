#include "stack.cpp"
#include <iostream>
#include <memory>

using namespace std;

int main() {
  // Creating a stack of integers using smart pointers
  unique_ptr<stack<int>> intStack = make_unique<stack<int>>(5);

  // Pushing elements into the stack
  intStack->push(10);
  intStack->push(20);
  intStack->push(30);

  // Printing the stack
  // cout << "Stack elements after pushing 10, 20, 30:" << endl;
  // intStack->print();
  //
  // // Popping an element
  // intStack->pop();
  // cout << "Stack after popping one element:" << endl;
  // intStack->print();
  //
  // // Getting the top element
  // cout << "Top element: " << intStack->pick() << endl;
  //
  // // Checking if the stack is empty
  // cout << "Is stack empty? " << (intStack->is_empty() ? "Yes" : "No") <<
  // endl;
  //
  // // Checking if the stack is full
  // cout << "Is stack full? " << (intStack->is_full() ? "Yes" : "No") << endl;
  //
  // // Reversing the stack
  // intStack->reverse();
  // cout << "Stack after reversing:" << endl;
  // intStack->print();
  string s = "(()(()))";
  int val = intStack->Score_of_Parentheses(s);
  cout << val << endl;

  return 0;
}
