#include <iostream>
#include <vector>
#include <stdexcept>

// Recursive binary search on a sorted vector<int> 
bool binarySearch(const std::vector<int>& data, int target, int low, int high) {
	if (low > high) {
		return false; // Base case: interval empty
	}

	int mid = low + (high - low) / 2; // Safe mid point; Prevents potential overflow. 

	if (target == data[mid]) {
		return true; // found a match
	} 
	else if (target < data[mid]) {
		return binarySearch(data, target, low, mid - 1); // Search left half 
	} 
	else {
		return binarySearch(data, target,  mid + 1, high);
	}
}

// A helper function for clean API: hides low/high parameters from the user. 
bool binarySearch(const std::vector<int>& data, int target) {
	if (data.empty()) return false; 
	return binarySearch(data, target, 0, static_cast<int>(data.size()) - 1);
}

// -- Demonstration -- 
int main() {
	std::vector<int> numbers = { 1, 3, 5, 7, 9, 11, 13, 15 }; 

	std::cout << "Data: ";
	for (int n : numbers) std::cout << n << " ";
	std::cout << "\n\n";

	int target = 7;
	std::cout << "Searching for " << target << "...\n"; 
	bool found = binarySearch(numbers, target); 
	std::cout << (found ? "FOUND\n" : "NOT FOUND.\n");

	target = 8; 
	std::cout << "Searching for " << target << "...\n";
	found = binarySearch(numbers, target);
	std::cout << (found ? "FOUND\n" : "NOT FOUND.\n");

	return 0;
}