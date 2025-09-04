/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 09-03-2025
* 
* Brief: 
*	A program that reads a list of integers into an array and outputs those integers in reverse. 
*	The first integer provided indicates how many integers follow. 
*/

#include <iostream>
#include <limits>					// numeric_limits
using namespace std; 

int main() {

	int numCount = 0;													// How many numbers the user will enter. 
	int* numArray = nullptr;											// Dynamic array pointer. 

	while (true)														// Loop until valid first int input.
	{
		cout << "Enter a list of elements, beginning with the number of elements, separated by a space: "; 
		
		// Read numCount, which is the first number. 
		if (!(cin >> numCount))											// Fail on non-int
		{
			cin.clear();												// Clear error flags from failed input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');		// Discard rest of line including \n
			cout << "First value must be an integer. \n"; 
			continue;													// Reprompt
		}
		
		// Validate numCount within bounds 0 - 20
		if (numCount < 0 || numCount > 20) 
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Count must be between the bounds [0, 20]. \n";
			continue;
		}

		// With valid numCount, allocate Dynamic Array pointer with numCount. 
		delete[] numArray;												// Redundant on first iteration. Frees previous allocation on later iterations
		numArray = (numCount > 0) ? new int[numCount] : nullptr;		// Allocate size. 

		// Reads only numCount amount of integers, fails on non-int. 
		bool ok = true; 
		for (int i = 0; i < numCount; i++)
		{
			if (!(cin >> numArray[i]))									// waits for numbers. Fails on non integers. 
			{
				ok = false; 
				break; 
			}
		}

		if (!ok) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid number encountered. Try again.\n"; 
			continue; 
		}

		// Discard extra inputs the user provided on the same line. 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// On success, print results in reverse 
		cout << "Count = " << numCount << "\nNumbers: "; 
		for (int i = 0; i < numCount; i++)
		{
			cout << numArray[numCount - i - 1] << ", ";
		}
		break;
	}
	cout << "\n";						// Spacing 
	delete[] numArray;					// Free memory once done. 
	return 0;
}