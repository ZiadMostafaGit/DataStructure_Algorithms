#include <iostream>
#include <memory>
#include <queue>  // For std::queue
#include <vector> // Not strictly needed, but common for dynamic arrays

// Node structure for the Binary Tree
template <typename T> struct Node {
  T val;
  std::shared_ptr<Node<T>> left;
  std::shared_ptr<Node<T>> right;

  Node(T v) : val(v), left(nullptr), right(nullptr) {}
};

// Binary Tree structure
template <typename T> class BinaryTree {
public:
  std::shared_ptr<Node<T>> root;

  BinaryTree() : root(nullptr) {}

  bool isEmpty() const { return root == nullptr; }

  void insertLevelOrder(T val) {
    std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(val);
    if (isEmpty()) {
      root = newNode;
      return;
    }

    std::queue<std::shared_ptr<Node<T>>> q;
    q.push(root);

    while (!q.empty()) {
      std::shared_ptr<Node<T>> current = q.front();
      q.pop();

      if (current->left == nullptr) {
        current->left = newNode;
        return;
      } else {
        q.push(current->left);
      }

      if (current->right == nullptr) {
        current->right = newNode;
        return;
      } else {
        q.push(current->right);
      }
    }
  }

  void inorderTraverse() const {
    if (isEmpty()) {
      std::cout << "tree is empty" << std::endl;
      return;
    }
    inorderRecursive(root);
    std::cout << std::endl;
  }

private:
  void inorderRecursive(std::shared_ptr<Node<T>> current) const {
    if (current) {
      inorderRecursive(current->left);
      std::cout << current->val << " ";
      inorderRecursive(current->right);
    }
  }
};

int main() {
  BinaryTree<unsigned int> binary;
  binary.insertLevelOrder(1);
  binary.insertLevelOrder(2);
  binary.insertLevelOrder(3);
  binary.insertLevelOrder(4);
  binary.insertLevelOrder(5);
  binary.insertLevelOrder(6);
  binary.insertLevelOrder(7);

  binary.inorderTraverse();

  return 0;
}
