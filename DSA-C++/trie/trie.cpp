#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Node {
public:
  unique_ptr<Node> childs[26];
  bool is_leaf;

  Node() {
    is_leaf = false;
    for (int i = 0; i < 26; i++) {
      childs[i] = nullptr;
    }
  }
};

class Trie {
private:
  unique_ptr<Node> root;

public:
  Trie() { root = make_unique<Node>(); }

  void insert(string str) {
    Node *current = root.get();

    int index = 0;
    for (char c : str) {
      index = char_to_index(c);
      if (!current->childs[index]) {
        current->childs[index] = make_unique<Node>();
      }
      current = current->childs[index].get();
    }
    current->is_leaf = true;
  }
  bool search(string str) {
    int index = 0;
    Node *current = root.get();
    for (char c : str) {
      index = char_to_index(c);
      if (!current->childs[index]) {
        return false;
      }
      current = current->childs[index].get();
    }
    return true;
  }

  int char_to_index(char c) { return c - 'a'; }
};

int main() {

  Trie t = Trie();
  t.insert("hello");
  t.insert("my");
  t.insert("name");
  t.insert("is");
  t.insert("ziad");
  cout << t.search("hi") << endl;
  cout << t.search("name") << endl;
  cout << t.search("ziad") << endl;
  cout << t.search("ziab") << endl;
  cout << t.search("zied") << endl;
}
