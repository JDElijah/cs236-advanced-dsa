#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>			// for std::size_t 

/*
	A fixed capacity queue implemented using std::vector. 
	param T the type of elements stored in the queue. 
*/

template <typename T> 
class ArrayQueue {
private:
	std::vector<T> elements;			// underlying container. 
	std::size_t frontIndex = 0;			// index of the front element. 
	std::size_t rearIndex = 0;			// index where the next element will be inserted.
	std::size_t elementCount = 0;		// current number of element in the queue. 

public:
	static constexpr std::size_t DEFAULT_CAPACITY = 1000;

	/* CONSTRUCTS A QUEUE WITH A DEFAULT CAPACITY */
	ArrayQueue() : ArrayQueue(DEFAULT_CAPACITY) {}

	/* CONSTRUCTS A QUEUE WITH A GIVEN CAPACITY */
	explicit ArrayQueue(std::size_t capacity) : elements(capacity) {}

	/* RETURNS THE NUMBER OF ELEMENTS CURRENTLY STORED IN THE QUEUE */
	[[nodiscard]] std::size_t size() const noexcept { return elementCount; }

	/* CHECKS WHETHER THE QUEUE IS EMPTY */
	[[nodiscard]] bool isEmpty() const noexcept { return elementCount == 0; }

	/* CHECKS WHETHER THE QUEUE IS FULL */
	[[nodiscard]] bool isFull() const noexcept { return elementCount == elements.size(); }

	/* ADDS AN ELEMENT AT THE REAR OF THE QUEUE */
	void enqueue(const T& value) {
		if (isFull()) throw std::runtime_error("Queue is full!");

		elements[rearIndex] = value;
		rearIndex = (rearIndex + 1) % elements.size(); // circular wrap-around 
		elementCount++;
	}

	/* REMOVES AND RETURNS THE FRONT ELEMENT OF THE QUEUE */
	T dequeue() {
		if (isEmpty()) throw std::runtime_error("Queue is empty");

		auto value = elements[frontIndex];
		frontIndex = (frontIndex + 1) % elements.size();
		elementCount--;
		return value;			// Returned by value (uses RVO) 
	}

	/* RETURNS (BUT DOES NOT REMOVE) THE FRONT ELEMENT */
	const T& front() const {
		if (isEmpty()) throw std::runtime_error("Queue is empty"); 
		return elements[frontIndex]; 
	}
};

int main() {
	ArrayQueue<int> queue(5);			// small capacity to test wrap-around
	
	std::cout << "Enqueueing 1, 2, 3\n"; 
	queue.enqueue(1); 
	queue.enqueue(2); 
	queue.enqueue(3); 

	std::cout << "Front element: " << queue.front() << "\n"; 
	std::cout << "Queue size: " << queue.size() << "\n"; 

	std::cout << "Dequeue: " << queue.dequeue() << "\n"; 
	std::cout << "Dequeue: " << queue.dequeue() << "\n";

	std::cout << "Enqueueing 4, 5, 6\n"; 
	queue.enqueue(4); 
	queue.enqueue(5); 
	queue.enqueue(6); // This should wrap around to teh beginning of the internal array. 

	std::cout << "Queue contents (dequeuing all elements):\n"; 
	while (!queue.isEmpty()) {
		std::cout << queue.dequeue() << " "; 
	}
	std::cout << "\n"; 

	// Test error handling 
	try {
		queue.dequeue();			// should throw
	}
	catch (const std::runtime_error& e) {
		std::cout << "Caught exception: " << e.what() << "\n";
	}

	return 0;
}