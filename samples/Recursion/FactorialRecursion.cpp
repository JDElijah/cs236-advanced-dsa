#include <iostream>
#include <stdexcept>

int factorial(int n) {
	if (n < 0) {
		throw std::invalid_argument("Argument must be non negative!");
	}
	else if (n == 0)
	{
		return 1; // base case
	}
	else {
		return n * factorial(n - 1); // recursive case
	}
}


int main() {
	try {
		int num = 5; 
		std::cout << "Factorial of " << num << " = " << factorial(num) << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0; 
}