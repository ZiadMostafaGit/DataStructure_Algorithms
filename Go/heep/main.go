// heap.go
package main

import "fmt"

type Heap struct {
	data []int
}

func NewHeap() *Heap {
	return &Heap{}
}

func (h *Heap) Push(val int) {
	h.data = append(h.data, val)
	h.heapifyUp(len(h.data) - 1)
}

func (h *Heap) Peek() (int, bool) {
	if len(h.data) == 0 {
		return 0, false
	}
	return h.data[0], true
}

func (h *Heap) Pop() (int, bool) {
	if len(h.data) == 0 {
		return 0, false
	}

	last := len(h.data) - 1
	h.data[0], h.data[last] = h.data[last], h.data[0]
	min := h.data[last]
	h.data = h.data[:last]

	if len(h.data) > 0 {
		h.heapifyDown(0)
	}

	return min, true
}

func (h *Heap) heapifyUp(index int) {
	for index > 0 {
		parent := (index - 1) / 2
		if h.data[index] < h.data[parent] {
			h.data[index], h.data[parent] = h.data[parent], h.data[index]
			index = parent
		} else {
			break
		}
	}
}

func (h *Heap) heapifyDown(index int) {
	size := len(h.data)
	for {
		left := 2*index + 1
		right := 2*index + 2
		smallest := index

		if left < size && h.data[left] < h.data[smallest] {
			smallest = left
		}
		if right < size && h.data[right] < h.data[smallest] {
			smallest = right
		}

		if smallest == index {
			break
		}

		h.data[index], h.data[smallest] = h.data[smallest], h.data[index]
		index = smallest
	}
}

func main() {
	heap := NewHeap()
	heap.Push(5)
	heap.Push(3)
	heap.Push(8)
	heap.Push(1)
	heap.Push(9)

	top, _ := heap.Peek()
	fmt.Println("Top:", top)

	for len(heap.data) > 0 {
		val, _ := heap.Pop()
		fmt.Println("Popped:", val)
		top, _ := heap.Peek()
		fmt.Println("Top:", top)
	}
}
