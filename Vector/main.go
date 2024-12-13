package main

import ()

func main() {
	arr := NewVector(10)
	// err := arr.pop()
	// if err != nil {
	// 	fmt.Println("{}", err)
	// }
	arr.push_back(4)
	arr.push_back(0)
	arr.push_back(1)
	arr.push_back(2)
	arr.push_back(3)
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
	arr.delete_position(2)
	// arr.right_rotation_with_steps(50000000)
	arr.print()

}
