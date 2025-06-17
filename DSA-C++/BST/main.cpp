#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <vector>

struct Node {
  int val;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;

  Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BSA {
public:
  std::shared_ptr<Node> root;

  BSA() : root(nullptr) {}

  bool isEmpty() const { return root == nullptr; }

  void insert(int val) {
    if (root == nullptr) {
      root = std::make_shared<Node>(val);
    } else {
      insertRecursive(root, val);
    }
  }

  void Delete(int val) {
    if (isEmpty()) {
      std::cout << "the tree is empty" << std::endl;
    }

    std::shared_ptr<Node> current = std::make_shared<Node>(root);
    deleteNode(current, val);
  }

  void inorderPrint() const {
    inorderPrintRecursive(root);
    std::cout << std::endl;
  }

  std::shared_ptr<Node> find(int val) const { return findRecursive(root, val); }

private:
  void insertRecursive(std::shared_ptr<Node> &current, int val) {
    if (val > current->val) {
      if (current->right == nullptr) {
        current->right = std::make_shared<Node>(val);
      } else {
        insertRecursive(current->right, val);
      }
    } else if (val < current->val) {
      if (current->left == nullptr) {
        current->left = std::make_shared<Node>(val);
      } else {
        insertRecursive(current->left, val);
      }
    }
  }

  void inorderPrintRecursive(std::shared_ptr<Node> current) const {
    if (current) {
      inorderPrintRecursive(current->left);
      std::cout << current->val << " ";
      inorderPrintRecursive(current->right);
    }
  }

  std::shared_ptr<Node> findRecursive(std::shared_ptr<Node> current,
                                      int val) const {
    if (current == nullptr || current->val == val) {
      return current;
    }
    if (val < current->val) {
      return findRecursive(current->left, val);
    } else {
      return findRecursive(current->right, val);
    }
  }

  std::optional<int> deleteNode(std::shared_ptr<Node> current, int val) {

    if (current == nullptr) {
      return std::nullopt;
    }
    if (current->val > val) {
      deleteNode(current->left, val);
    } else if (current->val < val) {
      deleteNode(current->right, val);
    } else {
      if (!current->left && !current->right) {
        current = nullptr;
      } else if (!current->right) {

      } else if (current->left && current->right) {
        std::shared_ptr<Node> sucssesor = get_min(current->right);
        current->val = sucssesor->val;
        deleteNode(current->right, current->val);
      }
    }
  }

  std::shared_ptr<Node> get_min(std::shared_ptr<Node> current) {
    while (!current->right && !current->left) {
      current = current->left;
    }
    return current;
  }
};

int main() {
  BSA bst;

  std::cout << "Is BST empty? " << (bst.isEmpty() ? "true" : "false")
            << std::endl;

  std::vector<int> values = {8, 3, 10, 1, 6, 14, 4, 7, 13};
  std::cout << "Inserting values: ";
  for (int val : values) {
    std::cout << val << " ";
    bst.insert(val);
  }
  std::cout << std::endl;

  std::cout << "Is BST empty after insertion? "
            << (bst.isEmpty() ? "true" : "false") << std::endl;

  std::cout << "Inorder traversal:" << std::endl;
  bst.inorderPrint();

  std::shared_ptr<Node> foundNode = bst.find(44);
  if (foundNode) {
    std::cout << "The find func returned something which is " << foundNode->val
              << std::endl;
  } else {
    std::cout << "The find func returned nullptr, which means we have a "
                 "problem (or value not found)."
              << std::endl;
  }

  return 0;
}
