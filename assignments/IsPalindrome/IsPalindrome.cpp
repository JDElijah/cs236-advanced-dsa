/*
	CS236 - Advanced Data Structures and Algorithm
	Joshua Elijah
	09-17-2025

	Brief: 
		A program that reads a list of integers from input and determines if the list
		is a palindrome. 
*/

#include <iostream>
#include <limits>
using namespace std; 

int main() {
	int numCount = 0; 
	int* numArray = nullptr; 
	
	/*
		Input Validation Loop
			Continue prompting the user until they provide: 
				A valid int count within the range of 1 - 20.
				Integer values for array. 
	*/
	while (true)
	{
		// Prompt for number of integers. 
		cout << "Enter number of integers (maximum 20): "; 
		
		// Check if input is an int. 
		if (!(cin >> numCount)) {
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Number of integers must be an integer. \n"; 
			continue; 
		}

		// Check if input is within range. 
		if (numCount <= 0 || numCount > 20)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Count must be between 1 and 20. \n";
			continue; 
		}
		
		// Allocate memory for int array. Free previous allocation.
		delete[] numArray; 
		numArray = new int[numCount];

		// Read ints into array. 
		bool validNumInput = true; 
		cout << "Enter each integer separated by a space: "; 
		for (int i = 0; i < numCount; i++)
		{
			if (!(cin >> numArray[i]))
			{
				validNumInput = false;
				break; 
			}
		}

		// Handle invalid int input. 
		if (!validNumInput)
		{
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid number encountered. Please try again. \n";
			continue;
		}

		// Clear extra junk on this line. 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		break;					// All inputs were valid and accepted. Exit the while loop 
	}

	/*
	*	Palindrome Check: 
	*		Compare first and last elements, moving toward the middle. 
	*		Only loop (check) halfway. Beyond is redundant. 
	*/
	bool isPalindrome = true;
	for (int i = 0; i < numCount / 2; i++) {  
		if (numArray[i] != numArray[numCount - i - 1])
		{
			isPalindrome = false;
			break; 
		}
	}

	// Output result. 
	if (isPalindrome)
	{
		cout << "\nInteger string is a palindrome"; 
	}
	else 
	{
		cout << "\nInteger string is not a palindrome";
	}

	cout << "\n"; 

	// Cleanup. Free dynamically allocated array. 
	delete[] numArray; 
	return 0; 
}


// Scratch Work

/*cout << "Array: ";
		for (int i = 0; i < numCount; i++)
		{
			cout << numArray[i] << " ";
		}*/

//int a = numArray[i];
//int b = numArray[numCount - i - 1];
//if (a != b)
//{
//	isPalindrome = false;
//	break;
//}