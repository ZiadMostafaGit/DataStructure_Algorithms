#include <iostream>
#include <memory>
using namespace std;

class Vector {
private:
  int capacity;
  int size;
  unique_ptr<int[]> arr;

  void double_capacity() {
    capacity *= 2;
    unique_ptr<int[]> new_arr = make_unique<int[]>(capacity);
    for (int i = 0; i < size; i++) {
      new_arr[i] = arr[i];
    }
    arr = move(new_arr);
  }

public:
  Vector() : capacity(100), size(0), arr(make_unique<int[]>(100)) {}

  Vector(int si)
      : capacity(max(100, si)), size(0), arr(make_unique<int[]>(capacity)) {}

  void push_back(int value) {
    if (size == capacity) {
      double_capacity();
    }
    arr[size] = value;
    size++;
  }

  void right_rotate() {
    if (size > 0) {
      int temp = arr[size - 1];
      for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
      }
      arr[0] = temp;
    }
  }

  void left_rotate() {
    if (size > 0) {
      int temp = arr[0];
      for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
      }
      arr[size - 1] = temp;
    }
  }

  void right_rotate_steps(int steps) {
    while (steps--) {
      right_rotate();
    }
  }

  int pop(int idx) {
    if (idx >= 0 && idx < size) {
      int item = arr[idx];
      for (int i = idx; i < size - 1; i++) {
        arr[i] = arr[i + 1];
      }
      size--;
      return item;
    }
    return -1;
  }

  int improved_search(int idx) {
    for (int i = 0; i < size - 1; i++) {
      if (arr[i] == idx) {
        int temp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = temp;
        return i;
      }
    }
    return -1;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << arr[i] << " ";
    }
    cout << endl;
  }
};
