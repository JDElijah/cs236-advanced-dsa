/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 11-29-2025
	Assignment: Build an AVL Tree from a Sorted Array
	Convention: balance = height(right) - height(left)
	Meaning: Negative = left-heavy, Positive = right-heavy
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
	int key; 
	int height;
	Node* left;
	Node* right; 

	explicit Node(int k)
		: key(k), height(1), left(nullptr), right(nullptr) {}
};

class BuildAVLFromArray {
public:
	// Helper: Return height of a node

	// Helper: Compute balance factor (right - left)

	// Recursively build AVL tree from sorted array

	// Inorder Travesal (Left -> Root -> Right)

	// Preorder Traversal (Root -> Left -> Right) 

	// Clean up memory (postorder delete) 

};

/// Main for testing 
int main() {
	return 0;
}