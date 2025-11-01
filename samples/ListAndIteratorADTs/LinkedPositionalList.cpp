#include <iostream>
#include <stdexcept>

/* Position Class*/
template <typename E> 
class Position {
public:
	virtual ~Position() = default; 

	// Returns the element stored at this position 
	virtual E& getElement() = 0; 

	// Returns the element stored at this position (const version)
	virtual const E& getElement() const = 0; 
};

/* PositionalList Class */
template <typename E> 
class PositionalList {
public:
	virtual ~PositionalList() = default; 

	virtual int size() const = 0; 
	virtual bool isEmpty() const = 0; 

	virtual  Position<E>* first() const = 0;
	virtual  Position<E>* last() const = 0;
	virtual  Position<E>* before(Position<E>* p) const = 0;
	virtual  Position<E>* after(Position<E>* p) const = 0;

	virtual  Position<E>* addFirst(const E& e) = 0; 
	virtual  Position<E>* addLast(const E& e) = 0; 
	virtual  Position<E>* addBefore(Position<E>* p, const E& e) = 0; 
	virtual  Position<E>* addAfter(Position<E>* p, const E& e) = 0;

	virtual E set(Position<E>* p, const E& e) = 0; 
	virtual E remove(Position<E>* p) = 0; 
};

/* LinkedPositionalList Implementation */
template <typename E> 
class LinkedPositionalList : public PositionalList<E> {
private: 
	// Nested Node class 
	class Node : public Position<E> {
	private: 
		E element; 
		Node* prev; 
		Node* next; 

	public: 
		Node(const E& e, Node* p, Node* n) : element(e), prev(p), next(n) {}

		E& getElement() override {
			if (next == nullptr) throw std::logic_error("Position no longer valid");
			return element; 
		}

		const E& getElement() const override {
			if (next == nullptr) throw std::logic_error("Position no longer valid");
			return element; 
		}

		Node* getPrev() const { return prev; }
		Node* getNext() const { return next; }
		void setElement(const E& e) { element = e; }
		void setPrev(Node* p) { prev = p; }
		void setNext(Node* n) { next = n; }
	};
	// end of node class. 

	Node* header;			// sentinel before first element 
	Node* trailer;			// sentinel after last element 
	int n;					// number of elements 

	/* Utility functions */
	Node* validate(Position<E>* p) const {
		Node* node = dynamic_cast<Node*>(p); 
		if (node == nullptr)
			throw std::invalid_argument("Invalid position type"); 
		if (node->getNext() == nullptr)
			throw std::invalid_argument("Position no longer in the list"); 
		return node; 
	}

	Position<E>* position(Node* node) const {
		if (node == header || node == trailer)
			return nullptr; 
		return node; 
	}

	Position<E>* addBetween(const E& e, Node* predecessor, Node* successor) {
		Node* newest = new Node(e, predecessor, successor); 
		predecessor->setNext(newest); 
		successor->setPrev(newest); 
		++n; 
		return newest; 
	}

public: 
	// Constructors and Destructors
	LinkedPositionalList() : n(0) {
		header = new Node(E{}, nullptr, nullptr);
		trailer = new Node(E{}, header, nullptr); 
		header->setNext(trailer); 
	}

	~LinkedPositionalList() override {
		while (!isEmpty())
			remove(first()); 
		delete header; 
		delete trailer; 
	}

	// Accessors 
	int size() const override { return n; }
	bool isEmpty() const override { return n == 0; }
	Position<E>* first() const override { return position(header->getNext()); }
	Position<E>* last() const override { return position(trailer->getPrev()); }

	Position<E>* before(Position<E>* p) const override {
		Node* node = validate(p); 
		return position(node->getPrev()); 
	}

	Position<E>* after(Position<E>* p) const override {
		Node* node = validate(p); 
		return position(node->getNext()); 
	}

	// Mutators 
	Position<E>* addFirst(const E& e) override {
		return addBetween(e, header, header->getNext()); 
	}

	Position<E>* addLast(const E& e) override {
		return addBetween(e, trailer->getPrev(), trailer);
	}

	Position<E>* addBefore(Position<E>* p, const E& e) override {
		Node* node = validate(p); 
		return addBetween(e, node->getPrev(), node);
	}

	Position<E>* addAfter(Position<E>* p, const E& e) override {
		Node* node = validate(p); 
		return addBetween(e, node, node->getNext());
	}

	E set(Position<E>* p, const E& e) override {
		Node* node = validate(p);
		E old = node->getElement(); 
		node->setElement(e);
		return old; 
	}

	E remove(Position<E>* p) override {
		Node* node = validate(p); 
		Node* predecessor = node->getPrev(); 
		Node* successor = node->getNext(); 
		predecessor->setNext(successor); 
		successor->setPrev(predecessor); 
		--n;

		E old = node->getElement(); 
		node->setNext(nullptr); 
		node->setPrev(nullptr); 
		delete node; 
		return old; 
	}
};

// Example 
int main() {
	LinkedPositionalList<int> list;

	auto* p1 = list.addFirst(10);
	auto* p2 = list.addAfter(p1, 20);
	auto* p3 = list.addLast(30);

	std::cout << "First element: " << list.first()->getElement() << "\n";
	std::cout << "Last element: " << list.last()->getElement() << "\n";
	std::cout << "Before last: " << list.before(p3)->getElement() << "\n";

	list.set(p2, 25);
	std::cout << "After updating middle to 25:\n";
	std::cout << "Elements in list: ";
	for (auto* pos = list.first(); pos != nullptr; pos = list.after(pos))
		std::cout << pos->getElement() << " ";
	std::cout << "\n";

	list.remove(p2);
	std::cout << "After removing middle, size = " << list.size() << "\n";
}