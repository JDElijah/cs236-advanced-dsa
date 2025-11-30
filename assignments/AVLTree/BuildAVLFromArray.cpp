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
#include <algorithm>	//  std::max, (to compute height of each node after building left and right subtrees)

struct Node {
	int key; 
	int height;
	Node* left;
	Node* right; 

	// Explicit prevents accidental implicit conversions, such as 'Node n = 10' 
	// We want to make sure Node objects are constructed clearly and correctly. 
	explicit Node(int k)
		: key(k), height(1), left(nullptr), right(nullptr) {}
};

class BuildAVLFromArray {
public:
	// Helper functions marked static because they don't depend on object instance of BuildAVLFromArray. They only
	// operate on the node pointer that is given as a parameter. Simply, static clarifies that the method belongs to the class instead, not 
	// an individual tree object.

	// Helper: Return height of a node
	static int height(const Node* n) {
		// TODO: return 0 if n is null, otherwise, n.height
		return n ? n->height : 0; 
	}
	
	// Helper: Compute balance factor (right - left)
	static int getBalance(const Node* n) {
		// TODO: return height(n.right) - height(n.left)
		if (!n) {
			return 0; 
		}
		return (height(n->right) - height(n->left));
	}

	// Recursively build AVL tree from sorted array
	Node* buildAVLFromSortedArray(const std::vector<int>& arr, int start, int end) {
		/* TODO:
		*	1. Base case: if start > end, return null
		*	2. Pick middle index as root. 
		*	3. Recursively build left and right subtrees
		*	4. Update height
		*	5. Return the root. 
		*/

		// 1.
		if (start > end) return nullptr; 

		// 2.
		int mid = start + (end - start) / 2; 
		Node* root = new Node(arr[mid]);

		// 3.
		root->left = buildAVLFromSortedArray(arr, start, mid - 1);
		root->right = buildAVLFromSortedArray(arr, mid + 1, end);

		// 4. 
		root->height = 1 + std::max(height(root->left), height(root->right)); 

		// 5. 
		return root; 
	}



	// Inorder Traversal (Left -> Root -> Right)
	static void inorder(const Node* node) {
		if (!node) return;
		inorder(node->left); 
		std::cout << node->key << " "; 
		inorder(node->right); 
	}

	// Preorder Traversal (Root -> Left -> Right) 
	static void preorder(const Node* node) {
		if (!node) return; 
		std::cout << node->key << " "; 
		preorder(node->left); 
		preorder(node->right);
	}

	// Clean up memory (postorder delete)
	// Needed because this implementation uses raw pointers. The tree doesn't free memory automatically. 
	// destroy() executes a post-order traversal and deletes every node to prevent memory leaks. 
	static void destroy(Node* node) {
		if (!node) return;
		destroy(node->left); 
		destroy(node->right); 
		delete node; 
	}

};

/// Main for testing 
int main() {
	BuildAVLFromArray tree; 

	std::vector<int> arr = { 10, 20, 30, 40, 50, 60, 70 };
	Node* root = tree.buildAVLFromSortedArray(arr, 0, arr.size() - 1);

	std::cout << "Inorder traversal: \n"; 
	BuildAVLFromArray::inorder(root); 
	std::cout << "\n"; 

	std::cout << "Preorder traversal: \n"; 
	BuildAVLFromArray::preorder(root); 
	std::cout << "\n"; 

	std::cout << "Root balance factor = " << BuildAVLFromArray::getBalance(root) << "\n"; 

	BuildAVLFromArray::destroy(root); 

	return 0;
}


/* 
* Notes: 
	Try matching buildAVLFromSortedArray declaration similarly to Java skeleton code.
	However, can be set to static as well, since it doesn't need object state.

	const Node* in helper functions: 
	- The function can read the node but cannot modify it 
	- Makes code safer and clearer. 
	- Prevents accidental changes while traversing or computing height/balance. 
*/