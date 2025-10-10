/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 09-10-2025
*
* Lab_Assignment_Recursion: Count_the_Digits
* 
* Brief:
*	Program that demonstrates a recursive method called digitCount() that takes a nonnegative
*	number as a parameter and returns the number of digits in the integer. 
*
* Notes at the end regarding digit limit with data type int. 
*/


#include <iostream>
#include <stdexcept>


int digitCount(int x) {
	// ensure valid x
	if (x < 0) {
		throw std::invalid_argument("Argument must be nonnegative.");
	} 
	else if (x / 10 == 0) { // base case , (when x is a single digit, division by 10 = 0) 
		return 1; // returning 1 because any single digit has 1 digit. 
	}
	return digitCount(x/10) + 1; // recursive case
	// each call divides x by 10, calls digitCount(), adds 1 to count the digit that was removed. 
	// the recursion removes one digit at a time until the base case is reached. 
	/*
		digitCount(1234)
			digitCount(123)
				digitCount(12)
					digitCount(1) 
		adding 1 each time. 1 + 1 + 1 + 1 = 4 digit number. 
	*/
	
}

int main() {
	int num; 

	while (true) {
		std::cout << "Enter an integer: "; 
		std::cin >> num; 

		// check for invalid input (non-numeric)
		if (std::cin.fail()) {
			std::cin.clear(); // clear the error flag 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer.\n";
			continue; 
		}

		// check for negative number 
		if (num < 0) {
			std::cout << "Number must be nonnegative. Try again.\n";
			continue; 
		}

		// valid input -- break out of loop. 
		break; 
	}
	try {
		int digits = digitCount(num);
		std::cout << "There are " << digits << " digits in the number " << num << std::endl; 
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}


/*
* Note: 
*  If the program must take in very large numbers, consider changing the 
* parameter type from int to std::string since int is limited to approx 10 digit numbers
* 
* int digitCount(const std::string& s) {
    for (char c : s) {
        if (!isdigit(c)) throw std::invalid_argument("Input contains non-digit characters.");
    }
    return s.size();
}
* other options are long long / or unsigned long long 
*/