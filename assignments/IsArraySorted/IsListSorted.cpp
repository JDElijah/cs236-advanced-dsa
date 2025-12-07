/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 12-06-2025
*
* Brief:
*	Write a program that reads a list of integers from input into an array and outputs "yes" 
	if the list is sorted in ascending order between two provided positions. Otherwise, output "no". 
	The first input specifies the number of items in the list. The next set of inputs is the list. 
	The last two inputs are the start and end positions (inclusive, 1-based). Assume the list contains 
	less than 20 integers and position 1 is the first element (positions are 1-based, so, for example, 
	an 8-element array would have positions 1-8).
*/

#include <iostream>
#include <vector>
using namespace std; 

int main() {
	
	// Declaring variables.
	int size; 
	vector<int> userValues(20); // Max size stated by assignment instructions

	// User Input: size
	cout << "Enter size of the array: ";
	cin >> size; 

	// User Input: array elements
	cout << "Enter " << size << " integers, separated by a space: ";
	for (int i = 0; i < size; i++) {
		cin >> userValues[i];
	}

	// User Input: start/end positions (1-based) 
	int left, right; 
	cout << "Enter start and end positions, separated by a space: "; 
	cin >> left >> right; 

	// Loop until user enters a valid range
	while (left < 1 || right < 1 || left > size || right > size || left > right) {
		cout << "Invalid range. Please enter a valid start and end position: "; 
		cin >> left >> right; 
	}

	// Positions are 1-based, provided by user.
	// Need to convert to 0-based indexing after validation.
	int startIdx = left - 1;
	int endIdx = right - 1;
	
	// Assume range is sorted. 
	bool sorted = true; 

	// for loop to determine if next element is less than previous element. If so, sorted is false. 
	for (int i = startIdx; i < endIdx; i++) {
		if (userValues[i] > userValues[i + 1])
		{
			sorted = false; 
			break; 
		}
	}


	// Result
	cout << "Sorted: " << (sorted ? "yes" : "no") << endl;
	
	return 0;
	
	
}


//Result 
//if (sorted) {
//	cout << "Sorted: " << "yes" << endl;
//}
//else
//{
//	cout << "Sorted: " << "no" << endl;
//}
