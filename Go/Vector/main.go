package main

import "fmt"

type Array struct {
	arr      []int
	size     int
	capacity int
}

func NewArray(capa int) *Array {
	return &Array{
		arr:      make([]int, capa),
		capacity: capa,
	}
}

func (a *Array) doubleCapacity() {
	a.capacity *= 2
	newArr := make([]int, a.capacity)
	copy(newArr, a.arr[:a.size])
	a.arr = newArr
}

func (a *Array) PushBack(num int) {
	if a.size == a.capacity {
		a.doubleCapacity()
	}
	a.arr[a.size] = num
	a.size++
}

func (a *Array) Pop() error {
	if a.size == 0 {
		return fmt.Errorf("array is empty")
	}
	a.size--
	return nil
}

func (a *Array) Insert(idx int, val int) error {
	if idx > a.size {
		return fmt.Errorf("index out of range")
	}

	if a.size == a.capacity {
		a.doubleCapacity()
	}

	for i := a.size; i > idx; i-- {
		a.arr[i] = a.arr[i-1]
	}
	a.arr[idx] = val
	a.size++
	return nil
}

func (a *Array) Print() {
	fmt.Println(a.arr[:a.size])
}

func (a *Array) RightRotation() {
	if a.size == 0 {
		return
	}

	last := a.arr[a.size-1]
	for i := a.size - 1; i > 0; i-- {
		a.arr[i] = a.arr[i-1]
	}
	a.arr[0] = last
}

func (a *Array) LeftRotation() {
	if a.size == 0 {
		return
	}

	first := a.arr[0]
	for i := 0; i < a.size-1; i++ {
		a.arr[i] = a.arr[i+1]
	}
	a.arr[a.size-1] = first
}

func (a *Array) RightRotationWithSteps(num int) {
	if a.size == 0 {
		return
	}
	num %= a.size
	for i := 0; i < num; i++ {
		a.RightRotation()
	}
}

func (a *Array) DeletePosition(idx int) (int, error) {
	if idx >= a.size {
		return 0, fmt.Errorf("index out of range")
	}

	deleted := a.arr[idx]
	for i := idx; i < a.size-1; i++ {
		a.arr[i] = a.arr[i+1]
	}
	a.size--
	return deleted, nil
}

func (a *Array) ImprovedSearch(num int) int {
	for i := 0; i < a.size; i++ {
		if a.arr[i] == num {
			if i > 0 {
				a.arr[i], a.arr[i-1] = a.arr[i-1], a.arr[i]
			}
			return i
		}
	}
	return -1
}

func main() {
	arr := NewArray(5)
	arr.PushBack(1)
	arr.PushBack(2)
	arr.PushBack(3)
	arr.Print()
	arr.RightRotation()
	arr.Print()
	arr.LeftRotation()
	arr.Print()
}
