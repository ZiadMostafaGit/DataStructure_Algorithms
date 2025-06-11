#include <iostream>
#include <memory> // For std::shared_ptr, std::weak_ptr
#include <vector> // For some operations like swap_kth, though not strictly needed for the list structure

// Node structure for the Doubly Linked List
struct Node {
  int val;
  std::shared_ptr<Node> next;
  std::weak_ptr<Node> prev; // Use weak_ptr to break circular references

  Node(int v)
      : val(v), next(nullptr), prev() {
  } // prev is default constructed to empty weak_ptr
};

// Doubly Linked List structure
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
      newNode->prev = tail; // Assign weak_ptr to prev
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
      head->prev = newNode; // Assign weak_ptr to prev
      head = newNode;
    }
    length++;
  }

  void popBack() {
    if (head == nullptr) {
      return;
    }
    if (head == tail) { // Only one node
      head = nullptr;
      tail = nullptr;
    } else {
      std::shared_ptr<Node> newTail =
          tail->prev.lock(); // Upgrade weak_ptr to shared_ptr
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
    if (head == tail) { // Only one node
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
      if (head) {
        head->prev.reset(); // Reset weak_ptr
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

  // Function to search for a value and return its index
  // Returns -1 if not found
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
    return -1; // Not found
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
      current = current->prev.lock(); // Upgrade weak_ptr to shared_ptr
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

    if (left_node == right_node) { // Same node or k is middle for odd length
      return;
    }

    // Handle adjacent nodes swap (left_node -> right_node or right_node ->
    // left_node)
    if (left_node->next == right_node) { // left is before right
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
               left_node) { // right is before left (shouldn't happen with k
                            // from ends)
      // This case is essentially symmetric to the above, handled by general
      // swap logic or by ensuring left_node is always "left" in order. For
      // simplicity, the general swap will handle it.
    }

    // General swap logic for non-adjacent nodes
    std::shared_ptr<Node> left_prev = left_node->prev.lock();
    std::shared_ptr<Node> left_next = left_node->next;
    std::shared_ptr<Node> right_prev = right_node->prev.lock();
    std::shared_ptr<Node> right_next = right_node->next;

    // Update pointers around left_node
    if (left_prev) {
      left_prev->next = right_node;
    } else {
      head = right_node;
    }
    if (left_next) {
      left_next->prev = right_node;
    } else {
      tail = right_node; // Should not happen if left_node is not tail
    }

    // Update pointers around right_node
    if (right_prev) {
      right_prev->next = left_node;
    } else {
      head = left_node; // Should not happen if right_node is not head
    }
    if (right_next) {
      right_next->prev = left_node;
    } else {
      tail = left_node;
    }

    // Swap next and prev pointers of the nodes themselves
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
      temp_prev = current->prev.lock(); // Upgrade weak_ptr

      current->next = temp_prev;
      current->prev = temp_next; // Convert shared_ptr to weak_ptr implicitly

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

  // Uncomment to test other functions
  // list.popFront();
  // list.popBack();
  // std::cout << "After popping front and back:" << std::endl;
  // list.printForward();

  // list.insert(1, 15);
  // std::cout << "After inserting 15 at index 1:" << std::endl;
  // list.printForward();

  // int search_val = 10;
  // int index = list.search(search_val)#;
#// if (index != -1) {
  //     std::cout << "Value " << search_val << " found at index: " << index <<
  //     std::endl;
  // } else {
  //     std::cout << "Value " << search_val << " not found." << std::endl;
  // }

  // std::shared_ptr<Node> mid_node = list.findMid();
  // if (mid_node) {
  //     std::cout << "Middle element: " << mid_node->val << std::endl;
  // } else {
  //     std::cout << "List is empty." << std::endl;
  // }

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
