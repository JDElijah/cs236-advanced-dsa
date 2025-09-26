#include <iostream>

// A generic doubly linked list template class
template <typename E> 
class DoublyLinkedList {
private: 
	// ----- nested Node struct -----
	struct Node {
		E element;					// data stored in this node. 
		Node* prev;					// pointer to the previous node.
		Node* next;					// point to next node. 

		// Constructor with defaults: initializes element (default E{} if none given), prev and next (nullptr if none given)
		Node(const E& e = E{}, Node* p = nullptr, Node* n = nullptr) : element(e), prev(p), next(n) {}
	};

	// ----- instance variable ----- 
	Node* header;					// sentinel at the front
	Node* trailer;					// sentiinel at the end 
	int count;						// number of elements

public: 
	// ----- constructor / destructor -----
	DoublyLinkedList() : count(0) {
		header = new Node();					// header sentinel 
		trailer = new Node();					// trailer sentinel
		header->next = trailer;
		trailer->prev = header;
	}

	~DoublyLinkedList() {
		clear(); 
		delete header; 
		delete trailer; 
	}

	// Disable copy (avoid shadow copies) 
	DoublyLinkedList(const DoublyLinkedList&) = delete; 
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete; 

	// ----- Access methods -----
	int size() const { return count; }
	bool empty() const { return count == 0; }

	// Return pointer to the first element, or nullptr if empty.
	E* first() const {
		if (empty()) return nullptr; 
		return &(header->next->element);
	}

	// Return pointer to the last element, or nullptr if empty 
	E* last() const {
		if (empty()) return nullptr; 
		return &(trailer->prev->element); 
	}

	// ----- Update methods -----
	void addFirst(const E& e) {
		addBetween(e, header, header->next);					// just after the header. 
	}

	void addLast(const E& e) {
		addBetween(e, trailer->prev, trailer);					// just before trailer. 	
	}

	// Remove and return first element (heap-allocated copy)
	E* removeFirst() {
		if (empty()) return nullptr; 
		return (remove(header->next));
	}

	// Remove and return last element (heap-allocated copy) 
	E* removeLast() {
		if (empty()) return nullptr; 
		return (remove(trailer->prev));
	}
	
	// Remove all nodes bewteen header and trailer
	void clear() {
		while (!empty()) {
			delete removeFirst();					// Free the heap-allocated element copy. 
		}
	}

private:
	// ----- Private helpers -----
	
	// Add node with an element between two existing nodes. 
	void addBetween(const E& e, Node* predecessor, Node* successor) {
		Node* newest = new Node(e, predecessor, successor); 
		predecessor->next = newest; 
		successor->prev = newest; 
		++count; 
	}

	// Remove a given node, return heap-allocated copy of its elements.
	E* remove(Node* node) {
		Node* predecessor = node->prev;
		Node* successor = node->next; 
		predecessor->next = successor; 
		successor->prev = predecessor; 

		E* value = new E(node->element);					// copy
		delete node;										// free node
		--count;
		return value;										// caller owns pointer
	}
};

int main() {
	DoublyLinkedList<int> list;

	list.addFirst(10);    // list: 10
	list.addLast(20);     // list: 10 <-> 20
	list.addLast(30);     // list: 10 <-> 20 <-> 30

	if (auto f = list.first())
		std::cout << "First: " << *f << "\n";
	if (auto l = list.last())
		std::cout << "Last: " << *l << "\n";

	if (auto removed = list.removeFirst()) {
		std::cout << "Removed first: " << *removed << "\n";
		delete removed;
	}

	if (auto removed = list.removeLast()) {
		std::cout << "Removed last: " << *removed << "\n";
		delete removed;
	}

	std::cout << "Size: " << list.size() << "\n";

	return 0;
}
