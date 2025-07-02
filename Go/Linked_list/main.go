// main3.go
package main

import "fmt"

type Node struct {
	val  int
	next *Node
}

type LinkedList struct {
	head   *Node
	tail   *Node
	length int
}

func NewLinkedList() *LinkedList {
	return &LinkedList{}
}

func (l *LinkedList) PushBack(val int) {
	node := &Node{val: val}

	if l.head == nil {
		l.head = node
		l.tail = node
	} else {
		l.tail.next = node
		l.tail = node
	}
	l.length++
}

func (l *LinkedList) PushFront(val int) {
	node := &Node{val: val}

	if l.head == nil {
		l.head = node
		l.tail = node
	} else {
		node.next = l.head
		l.head = node
	}
	l.length++
}

func (l *LinkedList) PopBack() {
	if l.head == nil {
		return
	}

	if l.head == l.tail {
		l.head = nil
		l.tail = nil
		l.length--
		return
	}

	current := l.head
	for current.next != l.tail {
		current = current.next
	}

	current.next = nil
	l.tail = current
	l.length--
}

func (l *LinkedList) PopFront() {
	if l.head == nil {
		return
	}

	if l.head == l.tail {
		l.head = nil
		l.tail = nil
	} else {
		l.head = l.head.next
	}
	l.length--
}

func (l *LinkedList) SwapHeadAndTail() {
	if l.head == nil || l.head == l.tail {
		return
	}

	prev := l.head
	for prev.next != l.tail {
		prev = prev.next
	}

	l.tail.next = l.head.next
	prev.next = l.head
	l.head.next = nil

	l.head, l.tail = l.tail, l.head
}

func (l *LinkedList) LeftRotate(k int) {
	if k <= 0 || l.length <= 1 {
		return
	}

	k %= l.length
	if k == 0 {
		return
	}

	l.tail.next = l.head
	current := l.head

	for i := 1; i < k; i++ {
		current = current.next
	}

	l.head = current.next
	l.tail = current
	l.tail.next = nil
}

func (l *LinkedList) GetNFromBack(index int) *int {
	if index < 0 || index >= l.length {
		return nil
	}

	target := l.length - index
	current := l.head
	for i := 0; i < target; i++ {
		current = current.next
	}
	return &current.val
}

func (l *LinkedList) helper(node *Node) {
	if node == nil {
		return
	}
	l.helper(node.next)
	fmt.Println(node.val)
}

func (l *LinkedList) PrintRev() {
	l.helper(l.head)
}

func (l *LinkedList) Print() {
	current := l.head
	for current != nil {
		fmt.Println(current.val)
		current = current.next
	}
}

func main() {
	list := NewLinkedList()
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)
	list.PushBack(4)
	list.PushBack(5)
	list.PushBack(6)
	list.Print()
}
