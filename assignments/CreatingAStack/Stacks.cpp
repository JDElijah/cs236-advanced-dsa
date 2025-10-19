/*
	CS236 - Advanced Data Structures and Algorithm
	Joshua Elijah
	10-18-2025

	Brief:
		A program that accepts the user's input of 4 strings that pushes them on a Stack and displays the Stack. 
		Then the program removes (pop) one item at a time, displaying the stack after each pop. 
*/
#include <iostream>
#include <stdexcept> // for std::underflow_error
#include <vector>

/* TEMPLATE STACK CLASS */
template <typename E> 
class Stack {
private: 
	std::vector<E> data;	// container. 

public:
	
	// Check if the stack is empty.
	bool isEmpty() const {
		return data.empty();
	}

	// Return current size of stack.
	int size() const {
		return data.size(); 
	}

	// Push an element onto the stack.
	void push(const E& element) {
		data.push_back(element); 
	}

	// Pop and return the top element of the stack. 
	E pop() {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty. Cannot pop.");
		}
		E removedTop = data.back(); 
		data.pop_back(); 
		return removedTop; 
	}

	// Return reference to the top element of the stack.
	const E& top() const {
		if (isEmpty()) {
			throw std::underflow_error("Error: Stack is empty. Cannot top.");
		}
		return data.back();
	}
	
	// Display the stack contents from the bottom to the top. 
	void display() const {
		if (isEmpty()) {
			std::cout << "Stack is empty!";
			return;
		}
		std::cout << "[ ";
		for (int i = 0; i < data.size(); ++i) {
			std::cout << data[i]; 
			if (i != data.size() - 1) std::cout << " ";
		}
		std::cout << " ]\n";
	}
};

/* MAIN PROGRAM */
int main() {
	Stack<std::string> demoStack;		// stack of strings
	const int STRING_COUNT = 4; 
	std::string item; 

	// Prompt the user for input. 
	std::cout << "Enter 4 items, separated by a space: ";
	
	int count = 0; 
	while (count < 4) {
		std::cin >> item; 
		demoStack.push(item);			// push each input onto the stack. 
		count++; 
	}

	// Display the full stack.
	std::cout << "Stack: ";
	demoStack.display(); 

	// Pop each item and display stack after each pop. 
	for (int i = 1; !demoStack.isEmpty(); ++i) {
		demoStack.pop(); 
		std::cout << "Stack after " << (i == 1 ? "first" : i == 2 ? "second" : i == 3 ? "third" : "fourth") << " item popped: ";
		demoStack.display(); 
	}

	std::cout << "\n\n";
	return 0; 
}
