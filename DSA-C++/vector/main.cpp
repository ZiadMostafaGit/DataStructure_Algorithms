#include <algorithm> // For std::rotate (more efficient rotations)
#include <iostream>
#include <vector> // For std::vector

// Custom Array (dynamic array) structure
class Array {
private:
  std::vector<int> arr;
  size_t current_size;
  size_t current_capacity; // std::vector manages this internally, but keeping
                           // for direct mapping

public:
  Array(size_t capa) : arr(capa), current_size(0), current_capacity(capa) {}

  // Double capacity is handled by std::vector's push_back/insert automatically
  // but explicit function can be implemented if wanted
  void doubleCapacity() {
    // std::vector handles this automatically when needed
    // If we want to strictly mimic Rust's manual doubling:
    current_capacity *= 2;
    arr.reserve(current_capacity); // Pre-allocates memory
  }

  void pushBack(int num) {
    // std::vector's push_back handles capacity increase automatically
    arr.push_back(num);
    current_size = arr.size();         // Keep track of logical size
    current_capacity = arr.capacity(); // Keep track of allocated capacity
  }

  // Using std::vector::pop_back()
  void pop() {
    if (arr.empty()) {
      std::cerr << "array is empty" << std::endl;
      return;
    }
    arr.pop_back();
    current_size = arr.size();
  }

  void insert(size_t idx, int val) {
    if (idx > current_size) {
      std::cerr << "index out of range" << std::endl;
      return;
    }
    arr.insert(arr.begin() + idx, val);
    current_size = arr.size();
    current_capacity = arr.capacity();
  }

  void print() const {
    std::cout << "[";
    for (size_t i = 0; i < current_size; ++i) {
      std::cout << arr[i];
      if (i < current_size - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
  }

  // Efficient right rotation using std::rotate
  void rightRotation() {
    if (current_size == 0)
      return;
    std::rotate(arr.rbegin(), arr.rbegin() + 1, arr.rend());
  }

  // Efficient left rotation using std::rotate
  void leftRotation() {
    if (current_size == 0)
      return;
    std::rotate(arr.begin(), arr.begin() + 1, arr.end());
  }

  void rightRotationWithSteps(size_t num) {
    if (current_size == 0)
      return;
    num %= current_size;
    if (num == 0)
      return;
    std::rotate(arr.rbegin(), arr.rbegin() + num, arr.rend());
  }

  int deletePosition(size_t idx) {
    if (idx >= current_size) {
      throw std::out_of_range("index out of range");
    }
    int deleted_val = arr[idx];
    arr.erase(arr.begin() + idx);
    current_size = arr.size();
    return deleted_val;
  }

  // Improved search: move found element one position forward
  ssize_t improvedSearch(int num) {
    for (size_t i = 0; i < current_size; ++i) {
      if (arr[i] == num) {
        if (i > 0) {
          std::swap(arr[i], arr[i - 1]);
        }
        return static_cast<ssize_t>(i);
      }
    }
    return -1; // Not found
  }
};

int main() {
  Array arr(5); // Initial capacity 5
  arr.pushBack(1);
  arr.pushBack(2);
  arr.pushBack(3);
  std::cout << "Initial array: ";
  arr.print(); // Expected: [1, 2, 3]

  std::cout << "After right rotation: ";
  arr.rightRotation();
  arr.print(); // Expected: [3, 1, 2]

  std::cout << "After left rotation: ";
  arr.leftRotation();
  arr.print(); // Expected: [1, 2, 3]

  arr.pushBack(4);
  arr.pushBack(5);
  arr.pushBack(6); // Will automatically resize underlying vector
  std::cout << "After more pushes: ";
  arr.print(); // Expected: [1, 2, 3, 4, 5, 6]

  std::cout << "After right rotation with 2 steps: ";
  arr.rightRotationWithSteps(2);
  arr.print(); // Expected: [5, 6, 1, 2, 3, 4]

  try {
    std::cout << "Deleting element at index 2: " << arr.deletePosition(2)
              << std::endl;
    std::cout << "Array after deletion: ";
    arr.print(); // Expected: [5, 6, 2, 3, 4] (if 1 was at index 2)
  } catch (const std::out_of_range &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  int search_val = 6;
  ssize_t found_idx = arr.improvedSearch(search_val);
  if (found_idx != -1) {
    std::cout << "Improved search for " << search_val
              << ". Original index: " << found_idx << ". Array: ";
    arr.print();
  } else {
    std::cout << search_val << " not found." << std::endl;
  }

  return 0;
}
