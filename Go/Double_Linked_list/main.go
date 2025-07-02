package main

import "fmt"

type Node struct {
	val  int
	next *Node
	prev *Node
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
	newNode := &Node{val: val}

	if l.head == nil {
		l.head = newNode
		l.tail = newNode
	} else {
		newNode.prev = l.tail
		l.tail.next = newNode
		l.tail = newNode
	}
	l.length++
}

func (l *LinkedList) PushFront(val int) {
	newNode := &Node{val: val}

	if l.head == nil {
		l.head = newNode
		l.tail = newNode
	} else {
		newNode.next = l.head
		l.head.prev = newNode
		l.head = newNode
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
	} else {
		l.tail = l.tail.prev
		l.tail.next = nil
	}
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
		l.head.prev = nil
	}
	l.length--
}

func (l *LinkedList) Insert(index, val int) {
	if index < 0 || index > l.length {
		return
	}

	if index == 0 {
		l.PushFront(val)
	} else if index == l.length {
		l.PushBack(val)
	} else {
		newNode := &Node{val: val}
		current := l.head
		for i := 0; i < index-1; i++ {
			current = current.next
		}

		newNode.next = current.next
		newNode.prev = current
		current.next.prev = newNode
		current.next = newNode
		l.length++
	}
}

func (l *LinkedList) Search(val int) *int {
	current := l.head
	index := 0
	for current != nil {
		if current.val == val {
			return &index
		}
		current = current.next
		index++
	}
	return nil
}

func (l *LinkedList) PrintForward() {
	current := l.head
	for current != nil {
		fmt.Print(current.val, " ")
		current = current.next
	}
	fmt.Println()
}

func (l *LinkedList) PrintBackward() {
	current := l.tail
	for current != nil {
		fmt.Print(current.val, " ")
		current = current.prev
	}
	fmt.Println()
}

func (l *LinkedList) FindMid() *int {
	if l.head == nil {
		return nil
	}

	slow := l.head
	fast := l.head

	for fast != nil && fast.next != nil {
		slow = slow.next
		fast = fast.next.next
	}

	return &slow.val
}

func (l *LinkedList) SwapKth(k int) {
	if k <= 0 || k > l.length {
		return
	}
	if 2*k-1 == l.length {
		return
	}

	left := l.head
	for i := 1; i < k; i++ {
		left = left.next
	}

	right := l.tail
	for i := 1; i < k; i++ {
		right = right.prev
	}

	if left == right {
		return
	}

	// Adjacent nodes
	if left.next == right {
		if left.prev != nil {
			left.prev.next = right
		} else {
			l.head = right
		}

		if right.next != nil {
			right.next.prev = left
		} else {
			l.tail = left
		}

		left.next = right.next
		right.prev = left.prev
		left.prev = right
		right.next = left
		return
	}

	// Swap links
	leftPrev := left.prev
	leftNext := left.next
	rightPrev := right.prev
	rightNext := right.next

	if leftPrev != nil {
		leftPrev.next = right
	} else {
		l.head = right
	}

	if leftNext != nil {
		leftNext.prev = right
	}

	if rightPrev != nil {
		rightPrev.next = left
	}

	if rightNext != nil {
		rightNext.prev = left
	} else {
		l.tail = left
	}

	left.prev = rightPrev
	left.next = rightNext
	right.prev = leftPrev
	right.next = leftNext
}

func (l *LinkedList) Reverse() {
	if l.head == nil || l.length < 2 {
		return
	}

	current := l.head
	for current != nil {
		current.prev, current.next = current.next, current.prev
		current = current.prev
	}
	l.head, l.tail = l.tail, l.head
}

func main() {
	list := NewLinkedList()

	list.PushBack(10)
	list.PushBack(20)
	list.PushBack(30)
	list.PushBack(5)
	list.PushBack(1)
	list.PushBack(200)
	list.PushFront(0)

	list.PrintForward()
	list.PrintBackward()
	list.Reverse()
	list.PrintForward()
}
