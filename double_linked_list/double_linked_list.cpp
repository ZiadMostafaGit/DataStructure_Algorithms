#include <iostream>
#include <memory>
using namespace std;

class dnode {
public:
  int data;
  // Each node uniquely owns the next node.
  std::unique_ptr<dnode> next;
  // 'prev' is a non‐owning raw pointer.
  dnode *prev;

  dnode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class doubl_list {
private:
  // 'head' owns the first node.
  std::unique_ptr<dnode> head;
  // 'tail' is a raw pointer to the last node.
  dnode *tail;
  int length;

public:
  doubl_list() : head(nullptr), tail(nullptr), length(0) {}

  // Helper: link two nodes by setting first's next and second's prev.
  // This function assumes that 'first' has an empty next.
  void link(dnode *first, dnode *second) {
    if (first) {
      // Take ownership of 'second' by assigning it to first->next.
      first->next.reset(second);
    }
    if (second) {
      second->prev = first;
    }
  }

  // Insert a new node with value 'val' at the tail.
  void insert_tail(int val) {
    auto new_node = std::make_unique<dnode>(val);
    new_node->prev = tail;
    dnode *new_node_raw = new_node.get();
    if (!head) {
      head = std::move(new_node);
      tail = head.get();
    } else {
      tail->next = std::move(new_node);
      tail = new_node_raw;
    }
    length++;
  }

  // Insert a new node with value 'val' at the head.
  void insert_head(int val) {
    auto new_node = std::make_unique<dnode>(val);
    if (!head) {
      head = std::move(new_node);
      tail = head.get();
    } else {
      new_node->next = std::move(head);
      new_node->next->prev = new_node.get();
      head = std::move(new_node);
    }
    length++;
  }

  // Insert a new node in sorted order.
  void insert_sorte(int val) {
    auto new_node = std::make_unique<dnode>(val);
    if (!head) {
      head = std::move(new_node);
      tail = head.get();
    } else if (val <= head->data) {
      new_node->next = std::move(head);
      new_node->next->prev = new_node.get();
      head = std::move(new_node);
    } else {
      dnode *curr = head.get();
      while (curr->next && curr->next->data < val) {
        curr = curr->next.get();
      }
      new_node->next = std::move(curr->next);
      if (new_node->next) {
        new_node->next->prev = new_node.get();
      } else {
        tail = new_node.get();
      }
      curr->next = std::move(new_node);
      curr->next->prev = curr;
    }
    length++;
  }

  // Print list from head to tail.
  void printfornt() {
    dnode *curr = head.get();
    while (curr) {
      cout << curr->data << " ";
      curr = curr->next.get();
    }
    cout << endl;
  }

  // Print list from tail to head.
  void printback() {
    dnode *curr = tail;
    while (curr) {
      cout << curr->data << " ";
      curr = curr->prev;
    }
    cout << endl;
  }

  // Delete the head node.
  void delete_head() {
    if (!head)
      return;
    head = std::move(head->next);
    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;
    length--;
  }

  // Delete the tail node.
  void delete_tail() {
    if (!tail)
      return;
    if (tail == head.get()) {
      head.reset();
      tail = nullptr;
    } else {
      // Traverse to find the node whose next is the tail.
      dnode *curr = head.get();
      while (curr->next.get() != tail)
        curr = curr->next.get();
      curr->next.reset();
      tail = curr;
    }
    length--;
  }

  // Delete a specific node given by pointer 'cur'.
  void delete_node(dnode *cur) {
    if (!cur)
      return;
    if (cur == head.get()) {
      delete_head();
      return;
    }
    // Find the unique_ptr that owns 'cur'.
    dnode *curr = head.get();
    while (curr && curr->next.get() != cur)
      curr = curr->next.get();
    if (curr && curr->next.get() == cur) {
      // Remove 'cur' by moving its next pointer.
      curr->next = std::move(cur->next);
      if (curr->next)
        curr->next->prev = curr;
      else
        tail = curr;
      length--;
    }
  }

  // Return a pointer to the first node containing 'val' (or nullptr if not
  // found).
  dnode *move(int val) {
    dnode *curr = head.get();
    while (curr) {
      if (curr->data == val)
        return curr;
      curr = curr->next.get();
    }
    return nullptr;
  }

  // Delete the first node with data equal to 'val'.
  void delete_node_with_key(int val) {
    if (!head)
      return;
    if (head->data == val) {
      delete_head();
      return;
    }
    dnode *curr = head.get();
    while (curr->next && curr->next->data != val)
      curr = curr->next.get();
    if (curr->next && curr->next->data == val) {
      if (curr->next.get() == tail)
        tail = curr;
      else
        curr->next->next->prev = curr;
      curr->next = std::move(curr->next->next);
      length--;
    }
  }
};
