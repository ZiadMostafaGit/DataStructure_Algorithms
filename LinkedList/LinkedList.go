package main

import (
	"fmt"
)

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
	tail := L.head
	for tail != nil {
		fmt.Println(tail.num)
		tail = tail.next
	}

}

func (L *LinkedList) PrintRev(Node *node) {
	L.PrintRev(Node.next)
	fmt.Println(Node.num)
}

// O(n)
func (L *LinkedList) PrintReverse() {

	tail := L.head
	if tail != nil {
		L.PrintRev(tail)
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

	tail := L.head
	for i := 0; i < itr; i++ {
		tail = tail.next

	}

	return tail.num
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

	tail := L.head
	for tail != nil {
		if tail.next.num == n {

			tail.next = tail.next.next
			L.lenght--

			break
		}
	}

}

func (L *LinkedList) swapHeadTail() {
	L.tail.next = L.head.next
	L.head.next = nil
	tail := L.tail
	for tail.next != L.tail {
		tail = tail.next
	}

	tail.next = L.head

	dummy := L.head
	L.head = L.tail
	L.tail = dummy
}

func (L *LinkedList) removeDuplic() {
	freq := make(map[int]int)
	tail := L.head
	freq[tail.num]++
	for tail != nil {

		freq[tail.next.num]++
		if freq[tail.next.num] > 1 {
			tail.next = tail.next.next
		}
		tail = tail.next

	}

}

func (L *LinkedList) moveToBack(num int) {

	if L.head.num == num {
		L.swapHeadTail()
	}
	tail := L.head
	for i := 0; i < L.lenght-1; i++ {
		if tail.next.num == num {
			L.tail.next = tail.next
			tail.next = tail.next.next
			L.tail = L.tail.next
			L.tail.next = nil
		}
		tail = tail.next
	}
}

type ListNode struct {
	Val  int
	Next *ListNode
}

func addTwoNumbers(L1 *ListNode, L2 *ListNode, rest int) *ListNode {
	if L1 == nil && L2 == nil {
		if rest != 0 {
			return &ListNode{1, nil}
		}
		return nil
	}

	if L1 != nil && L2 != nil {
		sum := L1.Val + L2.Val + rest
		rest = 0
		if sum > 9 {
			rest = 1
			node := &ListNode{sum - 10, nil}
			node.Next = addTwoNumbers(L1.Next, L2.Next, rest)
			return node
		} else {
			node := &ListNode{sum, nil}
			node.Next = addTwoNumbers(L1.Next, L2.Next, rest)
			return node
		}
	}

	if L1 != nil && L2 == nil {
		sum := L1.Val + rest
		rest = 0
		if sum > 9 {
			rest = 1
			node := &ListNode{sum - 10, nil}
			node.Next = addTwoNumbers(L1.Next, nil, rest)
			return node
		} else {
			node := &ListNode{sum, nil}
			node.Next = addTwoNumbers(L1.Next, nil, rest)
			return node
		}
	}

	if L1 == nil && L2 != nil {
		sum := L2.Val + rest
		rest = 0
		if sum > 9 {
			rest = 1
			node := &ListNode{sum - 10, nil}
			node.Next = addTwoNumbers(nil, L2.Next, rest)
			return node
		} else {
			node := &ListNode{sum, nil}
			node.Next = addTwoNumbers(nil, L2.Next, rest)
			return node
		}
	}

	return nil
}

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func deleteDuplicates(head *ListNode) *ListNode {
	if head == nil {
		return head
	}

	lastClean := head
	curr := head
	for curr != nil && curr.Next != nil {
		if curr.Val == curr.Next.Val {
			if curr == head {

				val := curr.Val
				for curr != nil {
					if curr.Val != val {
						break
					}
					curr = curr.Next
				}
				head = curr

			} else {
				val := curr.Val
				for curr != nil {
					if curr.Val != val {
						break
					}
					curr = curr.Next
				}

				lastClean.Next = curr
			}

		} else {

			lastClean = curr
			curr = curr.Next
		}
	}

	return head
}

// func main() {
//
// 	head := ListNode{1, nil}
// 	two := ListNode{2, nil}
// 	three := ListNode{3, nil}
// 	four := ListNode{3, nil}
// 	five := ListNode{4, nil}
// 	six := ListNode{4, nil}
// 	seven := ListNode{5, nil}
// 	head.Next = &two
// 	two.Next = &three
// 	three.Next = &four
// 	four.Next = &five
// 	five.Next = &six
// 	six.Next = &seven
// 	res := deleteDuplicates(&head)
// 	for res != nil {
// 		fmt.Println(res.Val)
// 		res = res.Next
// 	}
//
// }
