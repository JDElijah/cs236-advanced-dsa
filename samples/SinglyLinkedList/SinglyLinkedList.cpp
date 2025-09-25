#include <iostream>

// A generic singly linked list template class
template <typename E> 
class SinglyLinkedList {
private: 
	// ----- nested Node struct -----
	struct Node {
		E element;					// the data stored in this node. 
		Node* next;					// pointer to the next node (nullptr if none)

		// Contructor for Node: 
		// - Takes an element (by const reference to avoid unnecessary copying) 
		// - Takes an optional pointer to the next node (default to nullptr) 
		Node(const E& e, Node* n = nullptr) : element(e), next(n) {}
	};

	// ----- instance variables -----
	Node* head;					// pointer to the first node in the list (nullptr if empty)
	Node* tail;					// pointer to the last node in the list (nullptr if empty)
	int count;					// number of nodes in the list

public: 
	// ----- constructor / destructor -----
	SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

	// Destructor: 
	// Frees all nodes when the list object goes out of scope. 
	~SinglyLinkedList() {
		clear(); 
	}

	/*
	* Disable copy constructor and copy assignment operator.
	* Why? Because copying would only shadow-copy the pointers, 
	* which could cause double deletion and memory issues. 
	*/

	SinglyLinkedList(const SinglyLinkedList&) = delete; 
	SinglyLinkedList& operator=(const SinglyLinkedList&) = delete; 

	// ----- access methods -----
	int size() const { return count; }					// number of elements in the list.
	bool empty() const { return count == 0; }			// true if no elements.

	// Return a pointer to the first element, or nullptr if the list is empty
	E* first() const {
		return empty() ? nullptr : &head->element; 
	}

	// Return a pointer to the last element, or nullptr if the list is empty. 
	E* last() const {
		return empty() ? nullptr : &tail->element; 
	}

	// ----- update methods -----
	// Add an element at the front of the list.
	void addFirst(const E& e) {
		Node* newNode = new Node(e, head);					// new node points to old head. 
		head = newNode;										// head now points to new node. 
		if (count == 0) {									// special case: list was empty.
			tail = head;									// tail should also point to new node. 
		}
		++count;
	}

	// Add an element at the end of the list. 
	void addLast(const E& e) {
		Node* newNode = new Node(e);						// new node with next = nullptr. 
		if (count == 0) {
			head = newNode;									// special case: list was empty. 
		}
		else {
			tail->next = newNode;							// link to old tail to new node.
		}
		tail = newNode;										// update tail to new node. 
		++count; 
	}

	/*
	* Remove and return the first element. 
	* Returns nullptr if the list is empty. 
	* NOTE: retuns a *heap-allocated copy* of the element, 
	* so the caller is reposible for calling delete on it. 
	*/
	E* removeFirst() {
		if (empty()) return nullptr; 

		Node* oldHead = head;								// save pointer to current head. 
		E* value = new E(oldHead->element);					// make a copy of the element. 
		head = head->next;									// move head to next node. 
		delete oldHead;									// free old node 
		--count; 

		if (count == 0) {									// if list is now empty
			tail = nullptr;									// reset tail to nullptr 
		}
		return value;										// caller owns this pointer. 
	}

	/*
	* Remove and return the last element. 
	* Returns nullptr if the list is empty. 
	* NOTE: retuns a *heap-allocated copy"* of the element, 
	* so the caller is responsible for calling delete on it. 
	* Time complexity: O(n) due to traversal to the penultimate node. 
	*/
	E* removeLast() {
		if (empty()) return nullptr; 

		// special case: only one node 
		if (count == 1) {
			E* value = new E(head->element);					// copy element
			delete head;										// free the single node
			head = tail = nullptr;								// list becomes empty
			count = 0; 
			return value;										// caller owns this pointer. 
		}

		// General Case: find the node just before tail 
		Node* prev = head; 
		while (prev->next != tail) {			// stop at penultimate node. 
			prev = prev->next; 
		}

		// prev is penultimate, tail is last. 
		E* value = new E(tail->element);						// copy element to return 
		delete tail;											// free last node. 
		tail = prev;											// update tail
		tail->next = nullptr;									// new tail points to null 
		--count;

		return value;											// caller owns this pointer. 
	}

	// Remove all nodes from the list.
	void clear() {
		while (head != nullptr) {
			Node* oldHead = head; 
			head = head->next; 
			delete oldHead; 
		}
		tail = nullptr; 
		count = 0; 
	}
};

int main() {
	SinglyLinkedList<int> list; 

	// Add elements
	list.addFirst(10);		// list: 10 
	list.addLast(20);		// list: 10 -> 20
	list.addLast(30);		// list: 10 -> 20 -> 30

	// Access first and last
	if (auto f = list.first())
		std::cout << "First: " << *f << "\n"; 
	if (auto l = list.last())
		std::cout << "Last: " << *l << "\n";

	// Remove first element 
	if (auto removed = list.removeFirst()) {
		std::cout << "Removed: " << *removed << "\n"; 
		delete removed; // must delete sinve removeFirst() allocates. 
	}

	std::cout << "Size: " << list.size() << "\n";

	return 0; 
}