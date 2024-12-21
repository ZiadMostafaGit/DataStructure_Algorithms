package main

import "fmt"

type node struct {
	num  int
	next *node
}

// O(1)
func newNode(num int) *node {
	return &node{
		num: num,
	}
}

type LinkedList struct {
	head   *node
	tail   *node
	lenght int
}

// O(1)
func new() *LinkedList {
	return &LinkedList{}
}

// O(1)
func (L *LinkedList) isEmpty() bool {
	return L.head == nil
}

// O(1)
func (L *LinkedList) insret_end(num int) {
	newVal := newNode(num)
	if L.isEmpty() {
		L.head = newVal
		L.tail = newVal

	} else {

		L.tail.next = newVal
		L.tail = newVal
	}

	L.lenght++

}

// O(1)
func (L *LinkedList) insert_front(num int) {

	newVal := newNode(num)
	if L.isEmpty() {
		L.head = newVal
		L.tail = newVal

	} else {
		newVal.next = L.head
		L.head = newVal
	}

	L.lenght++
}

// O(n)
func (L *LinkedList) Print() {
	temp := L.head
	for temp != nil {
		fmt.Println(temp.num)
		temp = temp.next
	}

}

func (L *LinkedList) PrintRev(Node *node) {
	L.PrintRev(Node.next)
	fmt.Println(Node.num)
}

// O(n)
func (L *LinkedList) PrintReverse() {

	temp := L.head
	if temp != nil {
		L.PrintRev(temp)
	}

}

func (L *LinkedList) deleteFront() {

	if L.head != nil {
		L.head = L.head.next

	}
	if L.head == nil {
		L.tail = nil
	}

	L.lenght--
}

func (L *LinkedList) getNthFromBack(n int) int {

	if n > L.lenght {
		return -1
	}

	itr := L.lenght - n

	temp := L.head
	for i := 0; i < itr; i++ {
		temp = temp.next

	}

	return temp.num
}

func (L *LinkedList) delteWithKey(n int) {

	if L.isEmpty() {
		return
	}

	if L.head.num == n {
		L.head = L.head.next
		L.lenght--
		return
	}

	temp := L.head
	for temp != nil {
		if temp.next.num == n {

			temp.next = temp.next.next
			L.lenght--

			break
		}
	}

}

func (L *LinkedList) swapHeadTail() {
	L.tail.next = L.head.next
	L.head.next = nil
	temp := L.tail
	for temp.next != L.tail {
		temp = temp.next
	}

	temp.next = L.head

	dummy := L.head
	L.head = L.tail
	L.tail = dummy
}

func (L *LinkedList) removeDuplic() {
	freq := make(map[int]int)
	temp := L.head
	freq[temp.num]++
	for temp != nil {

		freq[temp.next.num]++
		if freq[temp.next.num] > 1 {
			temp.next = temp.next.next
		}
		temp = temp.next

	}

}

func (L *LinkedList) moveToBack(num int) {

	if L.head.num == num {
		L.swapHeadTail()
	}
	temp := L.head
	for i := 0; i < L.lenght-1; i++ {
		if temp.next.num == num {
			L.tail.next = temp.next
			temp.next = temp.next.next
			L.tail = L.tail.next
			L.tail.next = nil
		}
		temp = temp.next
	}
}
