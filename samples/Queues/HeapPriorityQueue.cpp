#pragma once 

#include <iostream>
#include <string>
#include <vector>			// for std::vector
#include <stdexcept>		// for std::runtime_error
#include <utility>			// for std::swap, std::move
#include <functional>		// for std::less, std::greater

/*
* HeapPriorityQueue
* 
* A binary heap implementation of a priority queue (min-heap by default)
* 
* Template parameters: 
* K			- type of key 
* V			- type of value
* Compare	- type of comparator (default std::less<K>) for min-heap
*				Must implement operator()(const K&, const K&) -> bool
*/

template <typename K, typename V, typename Compare = std::less<K>>
class HeapPriorityQueue {
private: 
	
	//---------- Nested Entry Struct ---------- //
	struct Entry {
	private:
		K key_; 
		V value_;
		
	public:
		Entry(const K& k, const V& v) : key_(k), value_(v) {}

		// Const getters for safe read-only access
		const K& key() const { return key_; }
		const V& value() const { return value_; }

		// non-const setters
		void setKey(const K& k) { key_ = k; }
		void setValue(const V& v) { value_ = v; }
	};

	std::vector<Entry> heap_;			// array-based heap storage
	Compare comp_;						// comparator object (defines heap ordering) 

	// ---------- Heap Helper Functions ---------- //
	
	// Index of parent 
	int parent(int j) const { return (j - 1) / 2; }

	// Indicies of left and right children
	int left(int j) const { return 2 * j + 1; }
	int right(int j) const { return 2 * j + 2; }

	bool hasLeft(int j) const { return left(j) < static_cast<int>(heap_.size()); }
	bool hasRight(int j) const { return right(j) < static_cast<int>(heap_.size()); }

	// Swap two elements in the heap 
	void swap(int i, int j) {
		std::swap(heap_[i], heap_[j]);
	}

	// ---------- Upheap / Downheap ---------- //
	
	// Restore heap property by moving element at index j up 
	void upheap(int j) {
		while (j > 0) {
			int p = parent(j);
			
			// if current element is NOT smaller than parent, heap property is satisfied
			if (!comp_(heap_[j].key(), heap_[p].key()))
				break;
			swap(j, p); // swap with parent
			j = p; // continue from parent index. 
		}
	}

	// Restore heap property by moving element at index j down
	void downheap(int j) {
		while (hasLeft(j)) {
			int leftIdx = left(j); 
			int smallChild = leftIdx; 

			if (hasRight(j)) {
				int rightIdx = right(j); 
				// pick the smaller child according to comparator
				if (comp_(heap_[rightIdx].key(), heap_[leftIdx].key()))
					smallChild = rightIdx; 
			}

			// If current element <= smallest child, heap property is satisfied. 
			if (!comp_(heap_[smallChild].key(), heap_[j].key()))
				break; 
			swap(j, smallChild);			// swap with smaller child 
			j = smallChild;					// continue from new child index
		}
	}

public: 
	// ---------- Constructors ---------- //

	// Default constructor
	// Uses  default comparator (Compare = std::less<K>) -> min-heap 
	HeapPriorityQueue() : heap_(), comp_() {}

	// Constructor with user-defined comparator 
	// Can be lambda, struct, or functor
	explicit HeapPriorityQueue(Compare comp) : heap_(), comp_(std::move(comp)) {}

	// ---------- Public Interface ---------- // 
	
	// Return true if heap is empty
	bool empty() const { return heap_.empty(); }

	// Return number of elements in the heap 
	int size() const { return heap_.size(); }

	// Return the top element without removing it
	const Entry& top() const {
		if (heap_.empty())
			throw std::runtime_error("Priority queue is empty"); 
		return heap_.front(); 
	}

	// Insert a new key-value pair 
	void insert(K key, V value) {
		heap_.emplace_back(std::move(key), std::move(value));			// Add to the end of the vector (bottom of heap)
		upheap(heap_.size() - 1);			// Move it up to restore heap property. 
	} 

	// Remove and return the top element. 
	Entry pop() {
		if (heap_.empty())
			throw std::runtime_error("Priority queue is empty"); 

		Entry result = heap_.front();		// store the min value
		swap(0, heap_.size() - 1);			// move last element to root 
		heap_.pop_back();					// Remove old root

		if (!heap_.empty())
			downheap(0);					// restore heap property from root. 
		return result;						
	}
};


int main() {
	// ----------- Test 1: Min-heap (default) -----------
	std::cout << "=== Min-Heap Test ===\n";
	HeapPriorityQueue<int, std::string> minHeap;

	minHeap.insert(5, "five");
	minHeap.insert(2, "two");
	minHeap.insert(8, "eight");
	minHeap.insert(1, "one");

	while (!minHeap.empty()) {
		auto e = minHeap.top();
		std::cout << e.key() << " -> " << e.value() << "\n";
		minHeap.pop();
	}

	// ----------- Test 2: Max-heap using std::greater -----------
	std::cout << "\n=== Max-Heap Test ===\n";
	HeapPriorityQueue<int, std::string, std::greater<int>> maxHeap;

	maxHeap.insert(5, "five");
	maxHeap.insert(2, "two");
	maxHeap.insert(8, "eight");
	maxHeap.insert(1, "one");

	while (!maxHeap.empty()) {
		auto e = maxHeap.top();
		std::cout << e.key() << " -> " << e.value() << "\n";
		maxHeap.pop();
	}

	// ----------- Test 3: Custom comparator (even numbers first) -----------
	std::cout << "\n=== Custom Comparator Test (even numbers first) ===\n";
	auto evenFirst = [](const int& a, const int& b) {
		// even numbers have higher priority
		if (a % 2 == 0 && b % 2 != 0) return true;
		if (a % 2 != 0 && b % 2 == 0) return false;
		return a < b; // otherwise natural ordering
		};

	HeapPriorityQueue<int, std::string, decltype(evenFirst)> customHeap(evenFirst);

	customHeap.insert(5, "five");
	customHeap.insert(2, "two");
	customHeap.insert(8, "eight");
	customHeap.insert(1, "one");
	customHeap.insert(4, "four");

	while (!customHeap.empty()) {
		auto e = customHeap.top();
		std::cout << e.key() << " -> " << e.value() << "\n";
		customHeap.pop();
	}

	return 0;
}
