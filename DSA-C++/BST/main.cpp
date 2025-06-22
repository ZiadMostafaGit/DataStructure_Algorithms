#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Node {
    int val;
    unique_ptr<Node> left;
    unique_ptr<Node> right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BSA {
public:
	Node*head=nullptr;
	Node*prev=nullptr;
    unique_ptr<Node> root;

    bool isEmpty() const {
        return root == nullptr;
    }

    void insert(int val) {
        insertRecursive(root, val);
    }

    void Delete(int val) {
        deleteNode(root, val);
    }

    void inorderPrint() const {
        inorderPrintRecursive(root.get());
        cout << endl;
    }

    Node* find(int val) const {
        return findRecursive(root.get(), val);
    }

private:


Node* convert_to_double_linked_list(){

inorder_swap(root.get());
	return head;
}



void inorder_swap(Node*current){

	if(!current){
		return ;
	}





	if(prev){

		prev->right=current;
		current->left=prev;




	}else{
		head=current;

	}
	prev=current;



}






    void insertRecursive(unique_ptr<Node>& node, int val) {
        if (!node) {
            node = make_unique<Node>(val);
            return;
        }
        if (val < node->val) {
            insertRecursive(node->left, val);
        } else if (val > node->val) {
            insertRecursive(node->right, val);
        }
    }

    void inorderPrintRecursive(const Node* node) const {
        if (node) {
            inorderPrintRecursive(node->left.get());
            cout << node->val << " ";
            inorderPrintRecursive(node->right.get());
        }
    }

    Node* findRecursive(Node* node, int val) const {
        if (!node || node->val == val) return node;
        if (val < node->val) return findRecursive(node->left.get(), val);
        else return findRecursive(node->right.get(), val);
    }

    Node* getMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    void deleteNode(unique_ptr<Node>& node, int val) {
        if (!node) return;

        if (val < node->val) {
            deleteNode(node->left, val);
        } else if (val > node->val) {
            deleteNode(node->right, val);
        } else {
            if (!node->left && !node->right) {
                node.reset(); 
		} else if (!node->left) {
                node = std::move(node->right);
            } else if (!node->right) {
                node = std::move(node->left);
            } else {
                Node* minRight = getMin(node->right.get());
                node->val = minRight->val;
                deleteNode(node->right, minRight->val);
            }
        }
    }
};









int main() {
    BSA bst;
    vector<int> values = {8, 3, 10, 1, 6, 14, 4, 7, 13};

    for (int val : values) {
        bst.insert(val);
    }

    cout << "Inorder traversal:\n";
    bst.inorderPrint();

    Node* found = bst.find(6);
    cout << "Find 6: " << (found ? "Found!" : "Not found!") << endl;

    cout << "Delete 6...\n";
    bst.Delete(6);
    bst.inorderPrint();

    cout << "Delete 8 (root)...\n";
    bst.Delete(8);
    bst.inorderPrint();
}

