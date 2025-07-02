package main

import "fmt"

type Node struct {
	val   int
	left  *Node
	right *Node
}

type BSA struct {
	root *Node
}

func NewBSA() *BSA {
	return &BSA{}
}

func (bst *BSA) IsEmpty() bool {
	return bst.root == nil
}

func (bst *BSA) Insert(val int) {
	if bst.root == nil {
		bst.root = &Node{val: val}
		return
	}
	insertRecursive(bst.root, val)
}

func insertRecursive(node *Node, val int) {
	if val > node.val {
		if node.right == nil {
			node.right = &Node{val: val}
		} else {
			insertRecursive(node.right, val)
		}
	} else if val < node.val {
		if node.left == nil {
			node.left = &Node{val: val}
		} else {
			insertRecursive(node.left, val)
		}
	}
}

func InorderPrint(node *Node) {
	if node == nil {
		return
	}
	InorderPrint(node.left)
	fmt.Print(node.val, " ")
	InorderPrint(node.right)
}

func (bst *BSA) Delete(val int) {
	bst.root = deleteNode(bst.root, val)
}

func deleteNode(node *Node, val int) *Node {
	if node == nil {
		return nil
	}

	if val < node.val {
		node.left = deleteNode(node.left, val)
	} else if val > node.val {
		node.right = deleteNode(node.right, val)
	} else {
		if node.left == nil {
			return node.right
		} else if node.right == nil {
			return node.left
		}

		minVal := findMin(node.right)
		node.val = minVal
		node.right = deleteNode(node.right, minVal)
	}
	return node
}

func findMin(node *Node) int {
	for node.left != nil {
		node = node.left
	}
	return node.val
}

func main() {
	bst := NewBSA()

	fmt.Println("Is BST empty?", bst.IsEmpty())

	values := []int{8, 3, 10, 1, 6, 14, 4, 7, 13}
	fmt.Println("Inserting values:", values)
	for _, val := range values {
		bst.Insert(val)
	}

	fmt.Println("Is BST empty after insertion?", bst.IsEmpty())

	fmt.Print("Inorder traversal after insertion: ")
	InorderPrint(bst.root)
	fmt.Println()

	toDelete := []int{3, 10, 8}
	for _, val := range toDelete {
		fmt.Printf("\nDeleting value: %d\n", val)
		bst.Delete(val)
		fmt.Print("Inorder traversal after deletion: ")
		InorderPrint(bst.root)
		fmt.Println()
	}
}
