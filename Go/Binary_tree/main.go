package main

import "fmt"

type Node[T any] struct {
	val   T
	left  *Node[T]
	right *Node[T]
}

type BinaryTree[T any] struct {
	root *Node[T]
}

func NewBinaryTree[T any]() *BinaryTree[T] {
	return &BinaryTree[T]{}
}

func (bt *BinaryTree[T]) IsEmpty() bool {
	return bt.root == nil
}

func (bt *BinaryTree[T]) InsertLevelOrder(val T) {
	newNode := &Node[T]{val: val}

	if bt.IsEmpty() {
		bt.root = newNode
		return
	}

	queue := []*Node[T]{bt.root}
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]

		if node.left == nil {
			node.left = newNode
			break
		} else {
			queue = append(queue, node.left)
		}

		if node.right == nil {
			node.right = newNode
			break
		} else {
			queue = append(queue, node.right)
		}
	}
}

func (bt *BinaryTree[T]) InorderRecursive(node *Node[T]) {
	if node == nil {
		return
	}
	bt.InorderRecursive(node.left)
	fmt.Print(node.val, " ")
	bt.InorderRecursive(node.right)
}

func (bt *BinaryTree[T]) InorderTraverse() error {
	if bt.IsEmpty() {
		return fmt.Errorf("tree is empty")
	}
	bt.InorderRecursive(bt.root)
	fmt.Println()
	return nil
}

func main() {
	binary := NewBinaryTree[uint32]()
	binary.InsertLevelOrder(1)
	binary.InsertLevelOrder(2)
	binary.InsertLevelOrder(3)
	binary.InsertLevelOrder(4)
	binary.InsertLevelOrder(5)
	binary.InsertLevelOrder(6)
	binary.InsertLevelOrder(7)
	binary.InorderTraverse()
}
