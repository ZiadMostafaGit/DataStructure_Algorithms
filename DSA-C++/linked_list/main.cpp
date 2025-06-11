#include <iostream>
#include <memory>

struct Node {
  int val;
  std::shared_ptr<Node> next;

  Node(int v) : val(v), next(nullptr) {}
};

class LinkedList {
public:
  std::shared_ptr<Node> head;
  std::shared_ptr<Node> tail;
  int length;

  LinkedList() : head(nullptr), tail(nullptr), length(0) {}

  void pushBack(int val) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    length++;
  }

  void pushFront(int val) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
    length++;
  }

  void popBack() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) {
      head = nullptr;
      tail = nullptr;
    } else {
      std::shared_ptr<Node> current = head;
      while (current->next != tail) {
        current = current->next;
      }
      current->next = nullptr;
      tail = current;
    }
    length--;
  }

  void popFront() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
    }
    length--;
  }

  void swapHeadAndTail() {
    if (head == nullptr || head == tail || length < 2) {
      return;
    }

    std::shared_ptr<Node> old_head = head;
    std::shared_ptr<Node> old_head_next = head->next;

    std::shared_ptr<Node> pre_tail = head;
    while (pre_tail->next != tail) {
      pre_tail = pre_tail->next;
    }

    head = tail;
    tail = old_head;

    head->next = old_head_next;
    pre_tail->next = tail;
    tail->next = nullptr;
  }

  void leftRotate(int k) {
    if (k <= 0 || head == nullptr || head == tail) {
      return;
    }

    int actual_rotations = k % length;
    if (actual_rotations == 0) {
      return;
    }

    tail->next = head;

    std::shared_ptr<Node> new_tail = head;
    for (int i = 0; i < actual_rotations - 1; ++i) {
      new_tail = new_tail->next;
    }

    head = new_tail->next;
    tail = new_tail;
    tail->next = nullptr;
  }

  int getNFromBack(int index) const {
    if (index <= 0 || index > length) {
      return -1;
    }

    std::shared_ptr<Node> slow = head;
    std::shared_ptr<Node> fast = head;

    for (int i = 0; i < index; ++i) {
      if (fast == nullptr) {
        return -1;
      }
      fast = fast->next;
    }

    while (fast != nullptr) {
      slow = slow->next;
      fast = fast->next;
    }

    return slow->val;
  }

  void printRevRecursive(std::shared_ptr<Node> current) const {
    if (current == nullptr) {
      return;
    }
    printRevRecursive(current->next);
    std::cout << current->val << std::endl;
  }

  void printRev() const { printRevRecursive(head); }

  void print() const {
    std::shared_ptr<Node> current = head;
    while (current) {
      std::cout << current->val << std::endl;
      current = current->next;
    }
  }
};

int main() {
  LinkedList list;
  list.pushBack(1);
  list.pushBack(2);
  list.pushBack(3);
  list.pushBack(4);
  list.pushBack(5);
  list.pushBack(6);

  std::cout << "Original list:" << std::endl;
  list.print();

  std::cout << "After pushFront(0):" << std::endl;
  list.pushFront(0);
  list.print();

  std::cout << "After popBack():" << std::endl;
  list.popBack();
  list.print();

  std::cout << "After popFront():" << std::endl;
  list.popFront();
  list.print();

  std::cout << "After swapHeadAndTail():" << std::endl;
  list.swapHeadAndTail();
  list.print();

  std::cout << "After leftRotate(10):" << std::endl;
  list.leftRotate(10);
  list.print();

  std::cout << "After leftRotate(2):" << std::endl;
  list.leftRotate(2);
  list.print();

  std::cout << "=======================" << std::endl;
  int n_from_back = 2;
  int res = list.getNFromBack(n_from_back);
  if (res != -1) {
    std::cout << n_from_back << "th element from back: " << res << std::endl;
  } else {
    std::cout << "Error: Invalid index or list is empty." << std::endl;
  }

  std::cout << "Print reversed:" << std::endl;
  list.printRev();

  return 0;
}
