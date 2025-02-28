#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_set>

using namespace std;

class Node {
public:
  int data;
  // Each node uniquely owns the next node.
  std::unique_ptr<Node> next;

  Node() : data(0), next(nullptr) {}
  Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
  // The list’s head is owned via a unique_ptr.
  std::unique_ptr<Node> head;
  // For convenience we keep a raw pointer to the tail (non‐owning).
  Node *tail;
  int length;

public:
  LinkedList() : head(nullptr), tail(nullptr), length(0) {}
  // No custom destructor is needed – unique_ptr cleans up automatically.
  ~LinkedList() = default;

  //////////////////////////////////////////////////////
  void insert_back(int value);
  void insert_front(int value);
  void insert_in_order(int value);
  // For merging a second list, we pass a pointer (non–owning).
  void insert_alternatig(LinkedList *linked2);
  ///////////////////////////////////////////////////////////////////

  //////////////////////////////////////////
  void delete_head();
  void delete_tail();
  int delete_with_key(int value);
  void delete_even_positions();
  // Given a raw pointer to a node, delete its successor.
  void delete_next_node(Node *node);
  ///////////////////////////////////////////////////////

  ////////////////////////////////////////////
  int get_nth_from_front(int value);
  int get_nth_from_back(int value);
  /////////////////////////////////////////////

  /////////////////////////////////////////////////
  bool is_the_same(LinkedList *linked);
  //////////////////////////////////////////////

  ///////////////////////////////////////////////
  void print_list();
  /////////////////////////////////////////////////

  /////////////////////////////////
  int get_length();
  // Returns a non–owning pointer to the head.
  Node *get_head();
  ///////////////////////////////

  /////////////////////////////////////////////////
  void swap_pair();
  // Swap the data of the two nodes.
  void swap_node(Node *node1, Node *node2);
  // (A simplified version that swaps just the head and tail data.)
  void swap_head_and_tail();
  ///////////////////////////////////////////////////

  /////////////////////////////////////////////
  void remove_duplicates();
  void remove_last_occurance(int value);
  void remove_all_repeted();
  //////////////////////////////////////////////////////////

  ////////// Reverse list /////////////
  void reverse_list();
  /////////////////////////////////////////////

  ///////////////////////////////////////////
  void lift_rotate(int value);
  ////////////////////////////////////////////

  ///////////////////////////////////////////
  void moveToEnd(int key);
  ////////////////////////////////////////////

  ///////////////////////////////////////////
  int max(Node *temp);
  ///////////////////////////////////////////

  ///////////////////////////////////////////
  void arrange_odd_even();
  ///////////////////////////////////////////

  ///////////////////////////////////////////
  void add_list(LinkedList *linked2);
  ///////////////////////////////////////////

  ///////////////////////////////////////////
  void delete_node(Node *prev, Node *cur);
  ///////////////////////////////////////////
};

//
// --- Implementation ---
//

void LinkedList::insert_back(int value) {
  auto new_node = std::make_unique<Node>(value);
  if (!tail) {
    head = std::move(new_node);
    tail = head.get();
  } else {
    tail->next = std::move(new_node);
    tail = tail->next.get();
  }
  length++;
}

void LinkedList::insert_front(int value) {
  auto new_node = std::make_unique<Node>(value);
  if (!head) {
    head = std::move(new_node);
    tail = head.get();
  } else {
    new_node->next = std::move(head);
    head = std::move(new_node);
  }
  length++;
}

void LinkedList::delete_head() {
  if (!head)
    return;
  head = std::move(head->next);
  length--;
  if (!head)
    tail = nullptr;
}

int LinkedList::get_nth_from_front(int n) {
  if (n > length || n < 1)
    return -1;
  if (n == length && tail)
    return tail->data;
  Node *temp = head.get();
  for (int i = 1; i < n; i++) {
    if (temp->next)
      temp = temp->next.get();
    else
      return -1;
  }
  return temp->data;
}

int LinkedList::get_nth_from_back(int n) {
  int index = length - n + 1;
  return get_nth_from_front(index);
}

bool LinkedList::is_the_same(LinkedList *linked) {
  if (length != linked->length)
    return false;
  Node *temp = head.get();
  Node *temp2 = linked->head.get();
  while (temp && temp2) {
    if (temp->data != temp2->data)
      return false;
    temp = temp->next.get();
    temp2 = temp2->next.get();
  }
  return true;
}

void LinkedList::print_list() {
  Node *temp = head.get();
  while (temp) {
    cout << temp->data << " ";
    temp = temp->next.get();
  }
  cout << endl;
}

int LinkedList::get_length() { return length; }

int LinkedList::delete_with_key(int value) {
  if (!head)
    return -1;
  int idx = 1;
  // Special case: key is in the head node.
  if (head->data == value) {
    delete_head();
    return idx;
  }
  Node *prev = head.get();
  // Use a pointer to the unique_ptr holding the next node.
  auto *curr_ptr = &prev->next;
  idx = 2;
  while ((*curr_ptr)) {
    if ((*curr_ptr)->data == value) {
      // If deleting the tail, update our tail pointer.
      if (!(*curr_ptr)->next)
        tail = prev;
      *curr_ptr = std::move((*curr_ptr)->next);
      length--;
      return idx;
    } else {
      prev = (*curr_ptr).get();
      curr_ptr = &((*curr_ptr)->next);
      idx++;
    }
  }
  return -1;
}

void LinkedList::swap_pair() {
  Node *current = head.get();
  while (current && current->next) {
    std::swap(current->data, current->next->data);
    current = current->next->next.get();
  }
}

void LinkedList::swap_node(Node *node1, Node *node2) {
  if (node1 && node2) {
    std::swap(node1->data, node2->data);
  }
}

void LinkedList::reverse_list() {
  if (!head || !head->next)
    return;
  // The current head will become the tail.
  Node *old_head = head.get();
  std::unique_ptr<Node> prev = nullptr;
  while (head) {
    auto next = std::move(head->next);
    head->next = std::move(prev);
    prev = std::move(head);
    head = std::move(next);
  }
  head = std::move(prev);
  tail = old_head;
}

void LinkedList::insert_in_order(int value) {
  auto new_node = std::make_unique<Node>(value);
  if (!head) {
    head = std::move(new_node);
    tail = head.get();
  } else if (value < head->data) {
    new_node->next = std::move(head);
    head = std::move(new_node);
  } else if (value > tail->data) {
    tail->next = std::move(new_node);
    tail = tail->next.get();
  } else {
    Node *current = head.get();
    while (current->next && current->next->data < value) {
      current = current->next.get();
    }
    new_node->next = std::move(current->next);
    current->next = std::move(new_node);
  }
  length++;
}

void LinkedList::delete_next_node(Node *n) {
  // Delete n->next (assumes n and n->next are non-null).
  assert(n && n->next);
  bool is_tail = (n->next->next == nullptr);
  n->next = std::move(n->next->next);
  length--;
  if (is_tail)
    tail = n;
}

void LinkedList::delete_even_positions() {
  if (length <= 1)
    return;
  Node *prv = head.get();
  while (prv && prv->next) {
    delete_next_node(prv);
    if (!prv->next)
      break;
    prv = prv->next.get();
  }
}

void LinkedList::swap_head_and_tail() {
  // Simplified version: just swap the data in head and tail.
  if (head && tail)
    std::swap(head->data, tail->data);
}

void LinkedList::lift_rotate(int value) {
  if (value < 1) {
    cout << "cannot rotate less than one time\n";
    return;
  }
  if (value == length)
    return;
  if (value > length)
    value = value % length;
  // Find the new tail (node at position 'value').
  Node *new_tail = head.get();
  for (int i = 1; i < value; i++) {
    new_tail = new_tail->next.get();
  }
  // Detach the list after new_tail.
  auto new_head = std::move(new_tail->next);
  new_tail->next = nullptr;
  // Find the tail of new_head and attach the original front.
  Node *temp = new_head.get();
  if (temp) {
    while (temp->next)
      temp = temp->next.get();
    temp->next = std::move(head);
  } else {
    new_head = std::move(head);
  }
  head = std::move(new_head);
  // Update tail by traversing to the end.
  Node *t = head.get();
  while (t && t->next)
    t = t->next.get();
  tail = t;
}

void LinkedList::delete_tail() {
  if (!head)
    return;
  if (!head->next) {
    head.reset();
    tail = nullptr;
    length--;
    return;
  }
  Node *curr = head.get();
  while (curr->next->next)
    curr = curr->next.get();
  curr->next.reset();
  tail = curr;
  length--;
}

void LinkedList::delete_node(Node *prev, Node *cur) {
  if (!prev) { // deleting the head node
    head = std::move(head->next);
  } else {
    if (prev->next.get() == cur) {
      prev->next = std::move(cur->next);
    }
  }
  length--;
  // Update tail if needed.
  if (!head)
    tail = nullptr;
  else {
    Node *t = head.get();
    while (t->next)
      t = t->next.get();
    tail = t;
  }
}

void LinkedList::remove_duplicates() {
  if (!head)
    return;
  unordered_set<int> seen;
  Node *curr = head.get();
  seen.insert(curr->data);
  while (curr && curr->next) {
    if (seen.find(curr->next->data) != seen.end())
      delete_next_node(curr);
    else {
      seen.insert(curr->next->data);
      curr = curr->next.get();
    }
  }
}

void LinkedList::remove_last_occurance(int value) {
  if (!head)
    return;
  Node *last_prev = nullptr;
  Node *curr = head.get();
  while (curr && curr->next) {
    if (curr->next->data == value)
      last_prev = curr;
    curr = curr->next.get();
  }
  if (last_prev)
    delete_next_node(last_prev);
}

void LinkedList::moveToEnd(int key) {
  // This version swaps data values so that nodes with value 'key'
  // eventually “bubble” toward the end of the list.
  Node *pKey = head.get();
  Node *pCrawl = head.get();
  while (pCrawl) {
    if (pCrawl != pKey && pCrawl->data != key) {
      std::swap(pKey->data, pCrawl->data);
      pKey = pKey->next.get();
    }
    if (pKey && pKey->data != key)
      pKey = pKey->next.get();
    pCrawl = pCrawl->next.get();
  }
}

int LinkedList::max(Node *temp) {
  if (!temp)
    return -1;
  return std::max(temp->data, max(temp->next.get()));
}

Node *LinkedList::get_head() { return head.get(); }

void LinkedList::arrange_odd_even() {
  if (length <= 1)
    return;
  int len = length;
  if (length % 2 != 0)
    len--;
  len /= 2;
  int i = 0;
  Node *prv = head.get();
  Node *cur = (prv ? prv->next.get() : nullptr);
  while (i < len && prv && cur) {
    insert_back(cur->data);
    delete_next_node(prv);
    if (!prv->next)
      break;
    cur = prv->next->next.get();
    prv = prv->next.get();
    i++;
  }
}

void LinkedList::insert_alternatig(LinkedList *linked2) {
  // Alternate merging: take nodes from linked2 and insert them into this list.
  Node *cur1 = head.get();
  while (cur1 && linked2->head) {
    // Detach the front node from linked2.
    auto alt_node = std::move(linked2->head);
    linked2->head = std::move(alt_node->next);
    // Insert alt_node after cur1.
    alt_node->next = std::move(cur1->next);
    cur1->next = std::move(alt_node);
    cur1 = cur1->next->next.get();
    length++;
  }
  // Update tail.
  Node *t = head.get();
  while (t && t->next)
    t = t->next.get();
  tail = t;
}

void LinkedList::add_list(LinkedList *linked2) {
  Node *cur = head.get();
  Node *cur2 = linked2->head.get();
  while (cur && cur2) {
    cur->data += cur2->data;
    if (cur->data >= 10) {
      if (cur->next) {
        cur->data -= 10;
        cur->next->data += 1;
      } else {
        cur->data -= 10;
        cur2->data += 1;
      }
    }
    cur = cur->next.get();
    cur2 = cur2->next.get();
  }
  if (cur && !cur->next)
    cur->next = std::move(linked2->head);
}

void LinkedList::remove_all_repeted() {
  // A simplified version: remove consecutive duplicates, leaving one instance.
  if (!head)
    return;
  Node *curr = head.get();
  while (curr && curr->next) {
    if (curr->data == curr->next->data)
      delete_next_node(curr);
    else
      curr = curr->next.get();
  }
}
