package main

import "fmt"

func main() {
	arr := NewVector(10)
	// err := arr.pop()
	// if err != nil {
	// 	fmt.Println("{}", err)
	// }
	arr.push_back(10)
	arr.push_back(20)
	arr.push_back(30)
	arr.push_back(40)
	arr.push_back(50)
	// fmt.Println("size is {}", arr.size)
	// err1 := arr.pop()
	// if err1 != nil {
	// 	fmt.Println("{}", err)
	// }
	//
	// arr.print()
	// arr.insert(3, 50)
	// arr.print()

	// arr.print()
	// arr.right_rotation()
	// arr.print()
	// arr.left_rotation()
	arr.print()
	// arr.delete_position(2)
	// arr.right_rotation_with_steps(50000000)
	res := arr.improved_search(30)
	if res == -1 {
		fmt.Println("not in the vector")
	} else {
		fmt.Println("in the index ", res)
	}
	arr.print()

}
