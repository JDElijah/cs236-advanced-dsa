#include <iostream>

// A generic singly linked list template class 
template <typename E>
class CircularlyLinkedList {
private: 
	// ----- nested Node struct -----
	struct Node {
		E element;					// The data stored in this node. 
		Node* next;					// Pointer to the next node. 

		Node(const E& e, Node* n = nullptr) : element(e), next(n) {}
	};

	// ----- instance variables -----
	Node* tail;						// Store the tail. (head is tail->next) 
	int count;						// number of nodes in the list. 

public: 
	// ----- constructor / destructor -----
	CircularlyLinkedList() : tail(nullptr), count(0) {}
	~CircularlyLinkedList() {
		clear(); 
	}

	// Disable copy (to avoid shadow copies) 
	CircularlyLinkedList(const CircularlyLinkedList&) = delete; 
	CircularlyLinkedList& operator=(const CircularlyLinkedList&) = delete; 

	// ----- access methods -----
	int size() const { return count; }
	int empty() const { return count == 0; }

	// Return a pointer to the first element, or nullptr if the list is empty 
	E* first() const {
		return empty() ? nullptr : &(tail->next->element); 
	}

	// Return a pointer to the last element, or nullptr if the list is empty
	E* last() const {
		return empty() ? nullptr : &tail->element;
	}
	
	// ----- update methods -----
	void rotate() {
		if (tail != nullptr)
		{
			tail = tail->next;					// old head becomes new tail. 
		}
	}

	// Add element at the front of the list. 
	void addFirst(const E& e) {
		if (count == 0) {
			tail = new Node(e);
			tail->next = tail;					// Circular link to itself.
		}
		else {
			Node* newest = new Node(e, tail->next);
			tail->next = newest; 
		}
		++count; 
	}

	// Add element at the end of the list.
	void addLast(const E& e) {
		addFirst(e);							// insert new node after tail
		tail = tail->next;						// advance tail to new node. 
	}

	// Remove and return first element (heap-allocated copy) 
	E* removeFirst() {
		if (empty()) return nullptr;

		Node* head = tail->next;				// node to remove
		E* value = new E(head->element);

		if (head == tail) {
			// only one node
			delete head;
			tail = nullptr;
		}
		else
		{
			tail->next = head->next;		// skip over head. 
			delete head;
		}

		--count;
		return value;
	}

	// Remove all nodes 
	void clear() {
		if (empty()) return; 

		Node* curr = tail->next;		// start from the head. 
		for (int i = 0; i < count; ++i)
		{
			Node* nextNode = curr->next; 
			delete curr; 
			curr = nextNode; 
		}

		tail = nullptr; 
		count = 0; 
		/*
			delete → frees the object in memory, but leaves the pointer dangling.
			nullptr → means the pointer is explicitly empty and safe to check.
		*/
	}
};

int main() {
	CircularlyLinkedList<int> clist;

	clist.addLast(10);   // list: 10 (circular)
	clist.addLast(20);   // list: 10 -> 20 -> back to 10
	clist.addLast(30);   // list: 10 -> 20 -> 30 -> back to 10

	if (auto f = clist.first())
		std::cout << "First: " << *f << "\n";
	if (auto l = clist.last())
		std::cout << "Last: " << *l << "\n";

	clist.rotate();  // now 20 is "head"

	if (auto f = clist.first())
		std::cout << "After rotate, first: " << *f << "\n";

	if (auto removed = clist.removeFirst()) {
		std::cout << "Removed: " << *removed << "\n";
		delete removed; // free the returned copy
	}

	std::cout << "Size: " << clist.size() << "\n";

	return 0;
}
