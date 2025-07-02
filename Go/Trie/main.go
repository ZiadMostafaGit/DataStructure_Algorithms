// trie.go
package main

import "fmt"

const AlphabetSize = 26

type Node struct {
	isLeaf bool
	child  [AlphabetSize]*Node
}

func NewNode() *Node {
	return &Node{}
}

type Trie struct {
	root *Node
}

func NewTrie() *Trie {
	return &Trie{root: NewNode()}
}

func (t *Trie) Insert(word string) {
	current := t.root
	for _, c := range word {
		index := t.charToIndex(c)
		if current.child[index] == nil {
			current.child[index] = NewNode()
		}
		current = current.child[index]
	}
	current.isLeaf = true
}

func (t *Trie) Search(word string) bool {
	current := t.root
	for _, c := range word {
		index := t.charToIndex(c)
		if current.child[index] == nil {
			return false
		}
		current = current.child[index]
	}
	return current.isLeaf
}

func (t *Trie) charToIndex(c rune) int {
	return int(c - 'a')
}

func main() {
	trie := NewTrie()

	words := []string{"cat", "cap", "can", "dog", "dove"}
	for _, word := range words {
		trie.Insert(word)
	}

	fmt.Println("Inserted words:", words)

	fmt.Println("Testing manually with search:")
	fmt.Println("Exists 'cat'? ", trie.Search("cat"))
	fmt.Println("Exists 'cab'? ", trie.Search("cab"))
	fmt.Println("Exists 'dove'? ", trie.Search("dove"))
	fmt.Println("Exists 'do'? ", trie.Search("do"))
}
