#include <iostream>
#include <memory>

struct Node {
  int val;
  std::shared_ptr<Node> next;
  std::weak_ptr<Node> prev;

  Node(int v)
      : val(v), next(nullptr), prev() {
}
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
      newNode->prev = tail;
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
      head->prev = newNode;
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
      std::shared_ptr<Node> newTail =
          tail->prev.lock();
      if (newTail) {
        newTail->next = nullptr;
        tail = newTail;
      }
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
      if (head) {
        head->prev.reset();
      }
    }
    length--;
  }

  void insert(int index, int val) {
    if (index < 0 || index > length) {
      return;
    }
    if (index == 0) {
      pushFront(val);
    } else if (index == length) {
      pushBack(val);
    } else {
      std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
      std::shared_ptr<Node> current = head;
      for (int i = 0; i < index - 1; ++i) {
        current = current->next;
      }
      newNode->next = current->next;
      newNode->prev = current;
      if (current->next) {
        current->next->prev = newNode;
      }
      current->next = newNode;
      length++;
    }
  }

  int search(int val) const {
    std::shared_ptr<Node> current = head;
    int index = 0;
    while (current) {
      if (current->val == val) {
        return index;
      }
      current = current->next;
      index++;
    }
    return -1;
  }

  void printForward() const {
    std::shared_ptr<Node> current = head;
    while (current) {
      std::cout << current->val << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

  void printBackward() const {
    std::shared_ptr<Node> current = tail;
    while (current) {
      std::cout << current->val << " ";
      current = current->prev.lock();
    }
    std::cout << std::endl;
  }

  std::shared_ptr<Node> findMid() const {
    if (head == nullptr) {
      return nullptr;
    }

    std::shared_ptr<Node> slow = head;
    std::shared_ptr<Node> fast = head;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }

  void swapKth(int k) {
    if (k <= 0 || k > length || 2 * k - 1 == length) {
      return;
    }

    std::shared_ptr<Node> left_node = head;
    for (int i = 1; i < k; ++i) {
      left_node = left_node->next;
    }

    std::shared_ptr<Node> right_node = tail;
    for (int i = 1; i < k; ++i) {
      right_node = right_node->prev.lock();
    }

    if (left_node == right_node) {
      return;
    }

    if (left_node->next == right_node) {
      std::shared_ptr<Node> left_prev = left_node->prev.lock();
      std::shared_ptr<Node> right_next = right_node->next;

      if (left_prev) {
        left_prev->next = right_node;
      } else {
        head = right_node;
      }

      if (right_next) {
        right_next->prev = left_node;
      } else {
        tail = left_node;
      }

      right_node->prev = left_prev;
      right_node->next = left_node;
      left_node->prev = right_node;
      left_node->next = right_next;
      return;
    } else if (right_node->next ==
               left_node) {
    }

    std::shared_ptr<Node> left_prev = left_node->prev.lock();
    std::shared_ptr<Node> left_next = left_node->next;
    std::shared_ptr<Node> right_prev = right_node->prev.lock();
    std::shared_ptr<Node> right_next = right_node->next;

    if (left_prev) {
      left_prev->next = right_node;
    } else {
      head = right_node;
    }
    if (left_next) {
      left_next->prev = right_node;
    } else {
      tail = right_node;
    }

    if (right_prev) {
      right_prev->next = left_node;
    } else {
      head = left_node;
    }
    if (right_next) {
      right_next->prev = left_node;
    } else {
      tail = left_node;
    }

    std::swap(left_node->next, right_node->next);
    std::swap(left_node->prev, right_node->prev);
  }

  void reverse() {
    if (head == nullptr || length < 2) {
      return;
    }

    std::shared_ptr<Node> current = head;
    std::shared_ptr<Node> temp_next = nullptr;
    std::shared_ptr<Node> temp_prev = nullptr;

    while (current) {
      temp_next = current->next;
      temp_prev = current->prev.lock();

      current->next = temp_prev;
      current->prev = temp_next;

      current = temp_next;
    }
    std::swap(head, tail);
  }
};

int main() {
  LinkedList list;

  list.pushBack(10);
  list.pushBack(20);
  list.pushBack(30);
  list.pushBack(5);
  list.pushBack(1);
  list.pushBack(200);
  list.pushFront(0);

  std::cout << "List forward:" << std::endl;
  list.printForward();
  std::cout << "List backward:" << std::endl;
  list.printBackward();

 list.popFront();
   list.popBack();
   std::cout << "After popping front and back:" << std::endl;
   list.printForward();

   list.insert(1, 15);
   std::cout << "After inserting 15 at index 1:" << std::endl;
   list.printForward();

   int search_val = 10;
   int index = list.search(search_val);
 if (index != -1) {
     std::cout << "Value " << search_val << " found at index: " << index <<
     std::endl;
   } else {
       std::cout << "Value " << search_val << " not found." << std::endl;
   }

   std::shared_ptr<Node> mid_node = list.findMid();
   if (mid_node) {
       std::cout << "Middle element: " << mid_node->val << std::endl;
   } else {
       std::cout << "List is empty." << std::endl;
   }

  std::cout << "Before swap_kth:" << std::endl;
  list.printForward();
  list.swapKth(2); // Example swap
  std::cout << "After swapping 2nd element from both ends:" << std::endl;
  list.printForward();

  std::cout << "Before reverse:" << std::endl;
  list.printForward();
  list.reverse();
  std::cout << "After reverse:" << std::endl;
  list.printForward();

  return 0;
}
