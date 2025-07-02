// package main

// import (
// 	"fmt"
// 	"strconv"
// 	"strings"
// )

// type Stack[T any] struct {
// 	data []T
// 	size int
// }

// func NewStack[T any](capacity int) *Stack[T] {
// 	return &Stack[T]{
// 		data: make([]T, 0, capacity),
// 	}
// }

// func (s *Stack[T]) Push(val T) {
// 	s.data = append(s.data, val)
// 	s.size++
// }

// func (s *Stack[T]) Pop() *T {
// 	if s.size == 0 {
// 		return nil
// 	}
// 	s.size--
// 	val := s.data[s.size]
// 	s.data = s.data[:s.size]
// 	return &val
// }

// func (s *Stack[T]) IsEmpty() bool {
// 	return s.size == 0
// }

// func (s *Stack[T]) Peek() *T {
// 	if s.size == 0 {
// 		return nil
// 	}
// 	return &s.data[s.size-1]
// }

// func (s *Stack[T]) Print() {
// 	for i := s.size - 1; i >= 0; i-- {
// 		fmt.Print(s.data[i], " ")
// 	}
// 	fmt.Println()
// }

// func (s *Stack[T]) InsertAtBottom(val T) {
// 	s.data = append([]T{val}, s.data...)
// 	s.size++
// }

// func reverseNumber(num int64) int64 {
// 	s := strconv.FormatInt(num, 10)
// 	stack := NewStack[byte](len(s))

// 	for i := 0; i < len(s); i++ {
// 		stack.Push(s[i])
// 	}

// 	var reversed []byte
// 	for !stack.IsEmpty() {
// 		reversed = append(reversed, *stack.Pop())
// 	}

// 	result, _ := strconv.ParseInt(string(reversed), 10, 64)
// 	return result
// }

// func validParentheses(s string) bool {
// 	stack := NewStack[byte](len(s))

// 	for i := 0; i < len(s); i++ {
// 		c := s[i]
// 		if c == '(' || c == '[' || c == '{' {
// 			stack.Push(c)
// 		} else if c == ')' || c == ']' || c == '}' {
// 			stack.Pop()
// 		}
// 	}

// 	return stack.IsEmpty()
// }

// func reverseSubWords(s *string) {
// 	words := strings.Fields(*s)
// 	var result strings.Builder

// 	for _, word := range words {
// 		stack := NewStack[rune](len(word))
// 		for _, c := range word {
// 			stack.Push(c)
// 		}
// 		for !stack.IsEmpty() {
// 			result.WriteRune(*stack.Pop())
// 		}
// 		result.WriteRune(' ')
// 	}

// 	*s = strings.TrimSpace(result.String())
// }

// func removeDuplicates(s string) string {
// 	stack := NewStack[rune](len(s))

// 	for _, c := range s {
// 		if stack.IsEmpty() || *stack.Peek() != c {
// 			stack.Push(c)
// 		} else {
// 			stack.Pop()
// 		}
// 	}

// 	var result []rune
// 	for !stack.IsEmpty() {
// 		result = append(result, *stack.Pop())
// 	}

// 	for i, j := 0, len(result)-1; i < j; i, j = i+1, j-1 {
// 		result[i], result[j] = result[j], result[i]
// 	}

// 	return string(result)
// }

// func reverseParentheses(s string) string {
// 	chars := []rune(s)
// 	stack := NewStack[int](len(chars))

// 	for i := 0; i < len(chars); i++ {
// 		if chars[i] == '(' {
// 			stack.Push(i)
// 		} else if chars[i] == ')' {
// 			res := stack.Pop()
// 			if res != nil {
// 				startIdx := *res + 1
// 				endIdx := i - 1
// 				for startIdx < endIdx {
// 					if chars[startIdx] == '(' || chars[startIdx] == ')' {
// 						startIdx++
// 						continue
// 					}
// 					if chars[endIdx] == '(' || chars[endIdx] == ')' {
// 						endIdx--
// 						continue
// 					}
// 					chars[startIdx], chars[endIdx] = chars[endIdx], chars[startIdx]
// 					startIdx++
// 					endIdx--
// 				}

// 			}

// 		}
// 	}

// 	var result strings.Builder
// 	for _, c := range chars {
// 		if c >= 'a' && c <= 'z' {
// 			result.WriteRune(c)
// 		}
// 	}

// 	return result.String()
// }

// func hello(n string) string {
// 	return "hello" + n
// }

// func main() {
// 	stack := NewStack[int](4)
// 	stack.Push(1)
// 	stack.Push(2)
// 	stack.Push(3)
// 	stack.Push(4)
// 	stack.Push(5)
// 	stack.Print()
// 	stack.InsertAtBottom(6)
// 	stack.Print()
// 	fmt.Println("res:", reverseParentheses("(u(love)i)"))
// 	fmt.Println("", hello("ziad"))
// }
