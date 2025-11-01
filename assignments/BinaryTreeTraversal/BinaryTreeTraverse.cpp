/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 11-01-2025
*
* Brief:
*	Program to traverse a binary tree using InOrder traversal with recursion. 
*/

#include <iostream>
using namespace std; 

/* BinaryTree class
		Represents a simple bst wuith recursive inorder traversal. 
*/
class BinaryTree {
public: 
	/* TreeNode struct to represent a single node in the binary tree. Nodes store data, and left and right children. */
	struct TreeNode {
		int data; 
		TreeNode* left; 
		TreeNode* right; 
		TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}			// Constructor that initializes node with a value a nullptr children. 
	};

	TreeNode* root; 
	BinaryTree() : root(nullptr) {}

	// Public method to initiate inorder traversal from a root. Prints notes in left -> root -> right order. 
	void inOrder() const {
		cout << "Nodes of binary tree on recursive InOrder traversal\n";
		inOrder(root); 
		cout << "\n"; 
	}

private: 
	// Private inOrder method that performs the inOrder traversal
	// Parameter: pointer to TreeNode being visited. 
	void inOrder(TreeNode* node) const {
		if (node == nullptr)
			return; 
		// Visit the left subtree
		inOrder(node->left);
		// Visit the node data. 
		cout << node->data << " "; // Print the node during traversal
		// Visit right subtree once left is done. 
		inOrder(node->right);
	}

public:
	// Static method to create and return a sample bst that uses the numeric values for an inorder traversal
	static BinaryTree create() {
		BinaryTree tree; 
		tree.root = new TreeNode(50); 
		tree.root->left = new TreeNode(30); 
		tree.root->right = new TreeNode(70); 
		
		tree.root->left->left = new TreeNode(20); 
		tree.root->left->right = new TreeNode(40);

		tree.root->left->left->left = new TreeNode(10); 

		tree.root->left->right->left = new TreeNode(35);
		tree.root->left->right->right = new TreeNode(45); 

		tree.root->right->right = new TreeNode(80); 
		return tree; 
	}
};

// Main function 
// Create a sample binary tree using the static method and prints out the nodes using recursive inorder traversal.
int main() {
	BinaryTree testTree = BinaryTree::create();
	testTree.inOrder(); 
	return 0;
}