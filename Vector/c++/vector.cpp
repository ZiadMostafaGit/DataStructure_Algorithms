#include "vector.h"
#include <iostream>
using namespace std;

Vector::Vector()
    : size(0), capacity(100), arr(std::make_unique<int[]>(capacity)) {}

Vector::Vector(int si)
    : size(0), capacity(si > 100 ? si : 100),
      arr(std::make_unique<int[]>(capacity)) {}

void Vector::push_back(int value) {
  if (size == capacity)
    double_capacity();
  arr[size++] = value;
}

void Vector::double_capacity() {
  capacity *= 2;
  auto new_arr = std::make_unique<int[]>(capacity);
  for (int i = 0; i < size; i++) {
    new_arr[i] = arr[i];
  }
  arr = std::move(new_arr);
}

void Vector::right_rotate() {
  if (size > 0) {
    int temp = arr[size - 1];
    for (int i = size - 1; i > 0; i--) {
      arr[i] = arr[i - 1];
    }
    arr[0] = temp;
  }
}

void Vector::left_rotate() {
  if (size > 0) {
    int temp = arr[0];
    for (int i = 0; i < size - 1; i++) {
      arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
  }
}

void Vector::right_rotate_steps(int steps) {
  while (steps--) {
    right_rotate();
  }
}

int Vector::pop(int idx) {
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

int Vector::improved_search(int idx) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == idx) {
      if (i > 0) {
        std::swap(arr[i], arr[i - 1]);
      }
      return i;
    }
  }
  return -1;
}

void Vector::print() const {
  for (int i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}
