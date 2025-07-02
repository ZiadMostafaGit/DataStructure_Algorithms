// main5.go
package main

import (
	"fmt"
	"strings"
	"unicode"
)

type Node[T any] struct {
	data T
	prev *Node[T]
}

type StackLinked[T any] struct {
	head *Node[T]
	size int
}

func NewStackLinked[T any]() *StackLinked[T] {
	return &StackLinked[T]{}
}

func (s *StackLinked[T]) IsEmpty() bool {
	return s.head == nil
}

func (s *StackLinked[T]) Push(data T) {
	newNode := &Node[T]{data: data}

	if s.head != nil {
		newNode.prev = s.head
	}
	s.head = newNode
	s.size++
}

func (s *StackLinked[T]) Pop() (T, error) {
	if s.head == nil {
		var zero T
		return zero, fmt.Errorf("stack is empty")
	}

	data := s.head.data
	s.head = s.head.prev
	s.size--
	return data, nil
}

func (s *StackLinked[T]) Peek() (T, error) {
	if s.head == nil {
		var zero T
		return zero, fmt.Errorf("stack is empty")
	}
	return s.head.data, nil
}

func (s *StackLinked[T]) Print() {
	current := s.head
	mid := 0
	if s.size >= 2 {
		mid = s.size / 2
	}
	index := 0
	for current != nil {
		if index == mid {
			fmt.Printf("[%v] ", current.data)
		} else {
			fmt.Printf("%v ", current.data)
		}
		index++
		current = current.prev
	}
	fmt.Println()
}

func evaluatePostFix(input string) (string, error) {
	stack := NewStackLinked[int]()
	tokens := strings.Fields(input)

	for _, token := range tokens {
		if len(token) != 1 {
			return "", fmt.Errorf("invalid token")
		}
		char := rune(token[0])

		if unicode.IsDigit(char) {
			stack.Push(int(char - '0'))
		} else {
			val1, err := stack.Pop()
			if err != nil {
				return "", err
			}
			val2, err := stack.Pop()
			if err != nil {
				return "", err
			}

			var result int
			switch char {
			case '+':
				result = val2 + val1
			case '-':
				result = val2 - val1
			case '*':
				result = val2 * val1
			case '/':
				if val1 == 0 {
					return "", fmt.Errorf("division by zero")
				}
				result = val2 / val1
			default:
				return "", fmt.Errorf("invalid operator")
			}
			stack.Push(result)
		}
	}

	result, err := stack.Pop()
	if err != nil {
		return "", err
	}
	return fmt.Sprint(result), nil
}

func fromInfixToPostfix(input string) (string, error) {
	stack := NewStackLinked[rune]()
	var output strings.Builder

	for _, char := range input {
		if unicode.IsDigit(char) || unicode.IsLetter(char) {
			output.WriteRune(char)
		} else if char == '(' {
			stack.Push(char)
		} else if char == '^' {
			stack.Push(char)
		} else if char == ')' {
			for {
				popped, err := stack.Pop()
				if err != nil {
					return "", err
				}
				if popped == '(' {
					break
				}
				output.WriteRune(popped)
			}
		} else {
			if stack.head == nil {
				stack.Push(char)
			} else {
				peek, _ := stack.Peek()
				if peek == '(' ||
					((char == '*' || char == '/') && (peek == '+' || peek == '-')) {
					stack.Push(char)
				} else {
					for {
						popped, err := stack.Pop()
						if err != nil {
							stack.Push(char)
							break
						}
						output.WriteRune(popped)

						peek, err := stack.Peek()
						if err != nil || peek == '(' {
							stack.Push(char)
							break
						}
					}
				}
			}
		}
	}

	for !stack.IsEmpty() {
		popped, _ := stack.Pop()
		output.WriteRune(popped)
	}

	return output.String(), nil
}

func asteroidCollision(astro []int) []int {
	stack := NewStackLinked[int]()

	for _, val := range astro {
		if stack.head == nil {
			stack.Push(val)
			continue
		}

		peek, _ := stack.Peek()
		if peek > 0 && val < 0 {
			for {
				peek, err := stack.Peek()
				if err != nil {
					stack.Push(val)
					break
				}

				if abs(peek) > abs(val) {
					break
				} else if abs(peek) < abs(val) {
					stack.Pop()
				} else {
					stack.Pop()
					break
				}
			}
		} else {
			stack.Push(val)
		}
	}

	var res []int
	for !stack.IsEmpty() {
		val, _ := stack.Pop()
		res = append(res, val)
	}
	reverseSlice(res)
	return res
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func reverseSlice(s []int) {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
}

func scoreOfParentheses(s string) int {
	var stack []int
	score := 0

	for _, c := range s {
		if c == '(' {
			stack = append(stack, score)
			score = 0
		} else {
			last := len(stack) - 1
			prev := stack[last]
			stack = stack[:last]
			if score*2 > 1 {
				score = prev + score*2
			} else {
				score = prev + 1
			}
		}
	}
	return score
}

func dailyTemperatures(temperatures []int) []int {
	stack := []int{}
	res := make([]int, len(temperatures))

	for i := 0; i <= len(temperatures)-2; i++ {
		if temperatures[i] < temperatures[i+1] {
			res[i] = 1
			for len(stack) > 0 {
				last := stack[len(stack)-1]
				if temperatures[last] < temperatures[i+1] {
					stack = stack[:len(stack)-1]
					res[last] = i - last + 1
				} else {
					break
				}
			}
		} else {
			stack = append(stack, i)
		}
	}
	return res
}

func main() {
	fmt.Println("== Daily Temperatures ==")
	temps := []int{30, 40, 50, 60}
	fmt.Println("Input:", temps)
	fmt.Print("Output: ")
	fmt.Println(dailyTemperatures(temps))

	fmt.Println("\n== Score of Parentheses ==")
	parentheses := "(()(()))"
	fmt.Println("Input:", parentheses)
	fmt.Println("Output:", scoreOfParentheses(parentheses))

	fmt.Println("\n== Asteroid Collision ==")
	asteroids := []int{10, 2, -5}
	fmt.Println("Input:", asteroids)
	fmt.Println("Output:", asteroidCollision(asteroids))

	fmt.Println("\n== Infix to Postfix ==")
	infixExpr := "a+b*(c^d-e)^(f+g*h)-i"
	fmt.Println("Infix:", infixExpr)
	postfixExpr, err := fromInfixToPostfix(infixExpr)
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("Postfix:", postfixExpr)
	}

	fmt.Println("\n== Evaluate Postfix ==")
	postfix := "2 3 1 * + 9 -"
	fmt.Println("Postfix:", postfix)
	value, err := evaluatePostFix(postfix)
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("Evaluated Value:", value)
	}
}
