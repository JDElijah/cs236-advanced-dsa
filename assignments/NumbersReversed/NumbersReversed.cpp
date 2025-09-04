#include <iostream>
#include <limits>
using namespace std; 

int main() {

	int numCount = 0; 
	int* numArray = nullptr; 

	while (true)
	{
		cout << "Enter a list of elements, beginning with the number of elements, separated by a space: "; 
		
		// Read numCount
		if (!(cin >> numCount)) 
		{
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "First value must be an integer. \n"; 
			continue;
		}
		
		if (numCount < 0 || numCount > 20) 
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Count must be bewteen the bounds [0, 20]. \n";
			continue;
		}

		delete[] numArray; 
		numArray = (numCount > 0) ? new int[numCount] : nullptr;

		// Read numCount integers
		bool ok = true; 
		for (int i = 0; i < numCount; i++)
		{
			if (!(cin >> numArray[i])) // waits for numbers. Fails on non integers. 
			{
				ok = false; 
				break; 
			}
		}
		// Discard any extra inputs the user provided on the same line 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (!ok) {
			cin.clear();
			cout << "Invalid number encountered. Try again.\n"; 
			continue; 
		}

		// On success
		cout << "Count = " << numCount << "\nNumbers: "; 
		for (int i = 0; i < numCount; i++)
		{
			cout << numArray[i] << ", ";
		}
		break;
	}
	delete[] numArray;
	return 0;
}