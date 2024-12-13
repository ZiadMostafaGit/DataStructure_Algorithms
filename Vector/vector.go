package main

import (
	"errors"
	"fmt"
)

type vector struct {
	arr      []int
	size     int
	capacity int
}

func NewVector(capa int) *vector {
	return &vector{
		arr:      make([]int, 0, capa),
		size:     0,
		capacity: capa,
	}

}

func (v *vector) doubleCapacity() {
	newArr := make([]int, v.size, v.capacity)
	copy(v.arr, newArr)
	v.arr = newArr
}
func (v *vector) push_back(num int) {
	if v.size == v.capacity {
		v.doubleCapacity()
	}
	v.arr = append(v.arr, num)
	v.size++

}

func (v *vector) pop() error {
	if v.size == 0 {
		return errors.New("vector is empty")
	}
	v.size--
	return nil
}

func (v *vector) insert(idx, val int) error {
	if idx < 0 || idx > v.capacity {
		return errors.New("index out of range ")
	}

	if v.size == v.capacity {
		v.doubleCapacity()
	}
	for i := v.size - 1; i >= idx; i-- {
		v.arr[i+1] = v.arr[i]
	}

	v.arr[idx] = val
	v.size++
	return nil

}

func (v *vector) print() {
	fmt.Println(v.arr[:v.size])
}

func (v *vector) right_rotation() {
	if v.size == v.capacity {
		v.doubleCapacity()
	}
	last_index := v.arr[v.size-1]
	for i := v.size - 1; i > 0; i-- {
		v.arr[i] = v.arr[i-1]
	}
	v.arr[0] = last_index
}
func (v *vector) left_rotation() {

	if v.size == v.capacity {
		v.doubleCapacity()
	}
	first_index := v.arr[0]
	for i := 0; i < v.size-2; i++ {
		v.arr[i] = v.arr[i+1]

	}
	v.arr[v.size-1] = first_index
}

func (v *vector) right_rotation_with_steps(num int) {

	if v.size == v.capacity {
		v.doubleCapacity()
	}
	num = num % v.size
	for i := 0; i < num; i++ {
		v.right_rotation()
	}

}

func (v *vector) delete_position(idx int) int {
	deleted := v.arr[idx]
	for i := idx; i < v.size-1; i++ {
		v.arr[i] = v.arr[i+1]
	}
	v.size--
	return deleted
}
