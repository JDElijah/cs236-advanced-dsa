//Refactored Code with OOP and Functions for IsPalindrome.

#include <iostream>
#include <limits>

class PalindromeChecker {
private: 
	int numCount;			// number of integers in the array. 
	int* numArray;			// pointer to dynamic array. 

public: 
	// Constructor
	PalindromeChecker() : numCount(0), numArray(nullptr) {}

	// Destructor to clean up memory 
	~PalindromeChecker() {
		delete[] numArray;
	}

	// Function to read input with validation. 
	void readInput() {
		while (true) {
			std::cout << "Enter number of integers (maximum 20): "; 

			if (!(std::cin >> numCount)) {
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Number of integers must be an integer.\n";
				continue; 
			}

			if (numCount <= 0 || numCount > 20) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Count must be between 1 and 20.\n"; 
				continue; 
			}

			delete[] numArray; 
			numArray = new int[numCount];

			bool validInput = true; 
			std::cout << "Enter each integer separated by a space: ";
			for (int i = 0; i < numCount; i++) {
				if (!(std::cin >> numArray[i])) {
					validInput = false; 
					break;
				}
			}

			if (!validInput) {
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid number encountered. Please try again.\n";
				continue;
			}

			// Clear extra input on this line. 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;			// success
		}
	}

	// Function to check if the array is a palindrome
	bool isPalindrome() const {
		for (int i = 0; i < numCount / 2; i++) {
			if (numArray[i] != numArray[numCount - i - 1]) {
				return false; 
			}
		}
		return true; 
	}

	// Function to print result 
	void printResult() const {
		if (isPalindrome()) {
			std::cout << "Integer string is a palindrome.\n";
		}
		else {
			std::cout << "Integer string is not a palindrome.\n";
		}
	}
};

// Main program entry point 
int main() {
	PalindromeChecker checker; 
	checker.readInput(); 
	checker.printResult(); 
	return 0;
}