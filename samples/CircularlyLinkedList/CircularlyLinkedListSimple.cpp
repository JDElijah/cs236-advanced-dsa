#include <iostream>
using namespace std; 

struct Node {
	int data; 
	Node* next; 

	Node(int val) : data(val), next(nullptr) {}
};

class CircularSinglyLinkedList {
private:
	Node* head; 
	Node* tail; 
	int size; 

public: 
	// Constructor
	CircularSinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Destructor
	~CircularSinglyLinkedList() {
		if (!head) return; 
		Node* curr = head; 
		do {
			Node* next = curr->next; 
			delete curr; 
			curr = next; 

		} while (curr != head);
	}

	// Insert at head
	void insertHead(int val) {
		Node* newNode = new Node{ val };
		if (!head) {
			head = tail = newNode; 
			newNode->next = newNode; 
		}
		else {
			newNode->next = head;
			tail->next = newNode;
			head = newNode;
		}
		size++; 
	} 

	// Insert at tail 
	void insertTail(int val) {
		Node* newNode = new Node{ val };
		if (!head) {
			head = tail = newNode; 
		}
		else {
			newNode->next = head;
			tail->next = newNode;
			tail = newNode;
		}
		size++; 
	}

	// Insert at position (0-based) 
	void insertNode(int pos, int val) {
		// invalid position 
		if (pos < 0 || pos > size) {
			cout << "Invalid position" << endl; 
			return; 
		}

		// insert at head
		if (pos == 0) {
			insertHead(val);
			return;
		}
		
		// insert at tail 
		if (tail == 0) {
			insertTail(val);
			return; 
		}

		Node* newNode = new Node{ val };
		Node* temp = head;
		for (int i = 0; i < pos - 1; i++) {
			temp = temp->next; 
		}
		newNode->next = temp->next; 
		temp->next = newNode; 
		size++;
	}

	// delete head 
	void deleteHead() {
		// empty list
		if (!head) return; 
		
		// 1 node in list. 
		if (head == tail)
		{
			delete head; 
			head = tail = nullptr;
		}
		else
		{
			Node* temp = head;
			head = head->next;
			tail->next = head;
			delete temp;
		}
		size--;
	}

	// delete by value
	void deleteValue(int val) {
		// if empty
		if (!head) return; 
		Node* curr = head; 
		Node* prev = tail; 

		do {
			if (curr->data == val) {
				if (curr == head) {
					deleteHead(); 
					return; 
				}
				// Main logic - deleting non-head node
				prev->next = curr->next; 

				if (curr == tail) {
					tail = prev;
				}
				delete curr; 
				size--; 
				return; 
			}
			prev = curr; 
			curr = curr->next; 
		} while (curr != head);
	}

	// Display the list. 
	void display() {
		if (!head) {
			cout << "List is empty!" << endl; 
			return;
		}
		Node* temp = head; 
		do {
			cout << temp->data << " "; 
			temp = temp->next; 
		} while (temp != head);
		cout << endl;
	}

	// get size
	int getSize() const { return size; }

	// Search for value
	bool search(int val) {
		if (!head) return false; 
		Node* temp = head; 
		do {
			if (temp->data == val) return true;
			temp = temp->next;
		} while (temp != head);
		return false;
	}
};

int main() {
	
	CircularSinglyLinkedList cll; 
	cll.insertHead(10); 
	cll.insertHead(20); 
	cll.insertTail(5); 
	cll.insertTail(1); 

	cout << "List: "; 
	cll.display();  // 20 10 5 1

	cll.insertNode(2, 99); 
	cout << "After inserting 99 at pos 2: "; 
	cll.display(); // 20 10 99 5 1

	cll.deleteValue(99); 
	cout << "After deleting 99: "; 
	cll.display(); // 20 10 5 1 

	cll.deleteHead(); 
	cout << "After deleting head: "; 
	cll.display(); // 10 5 1

	cout << "Size of list: " << cll.getSize() << endl;
	cout << "Search(5): " << (cll.search(5) ? "Found" : "Not found") << endl;
	return 0;
}