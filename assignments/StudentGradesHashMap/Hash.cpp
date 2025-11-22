/*
* CS236 - Advanced Data Structures and Algorithms
* Joshua Elijah
* 11-22-2025
* 
* Lab Assignment - Student Grades (Hash Map)
* 
* Brief:
*	Given a HashMap pre-filled with student names as keys and grades as values, 
*	complete main() by reading in the name of a student, outputting their original grade, 
*	and then reading in and outputting their new grade. Prompt the user to enter
*	the student's name and grade (separated by a new line). 
*/


#include <iostream>
#include <unordered_map> // conceptually equivalent to Java's HashMap. Both use an ADT using a hash table.
#include <string>

int main() {

	std::string studentName;
	double newGrade = 0.0;

	std::unordered_map<std::string, double> studentGrades;

	// Students' grades (pre-entered) 
	studentGrades.emplace("Harry Rawlins", 84.3); 
	studentGrades.emplace("Stephanie Kong", 91.0); 
	studentGrades.emplace("Shailen Tennyson", 78.6);
	studentGrades.emplace("Quincy Wraight", 65.4); 
	studentGrades.emplace("Janine Antinori", 98.2); 

	// TODO: 
	//		1. Read in new grade for a student
	//		2. output initial grade
	//		3. output new grade 

	 
	// Prompt user for student name.
	std::cout << "Enter the student's name:\n";
	std::getline(std::cin, studentName);

	// Prompt user for student's grade.
	std::cout << "Enter grade for " << studentName << ":\n";
	std::cin >> newGrade; 
	std::cout << '\n'; 

	// Look up the studentName's original grade. 
	auto iter = studentGrades.find(studentName);		// finds element with specific key.
	if (iter != studentGrades.end()) {					// .end() returns an iterator that points to past the last element in the container.
		std::cout << studentName << "'s original grade: " << iter->second << '\n';			// first and second refer to key-value pairs. first = key, second = value 
		iter->second = newGrade; 
		std::cout << studentName << "'s new grade: " << iter->second << '\n';
	}
	else {
		std::cout << "Student [" << studentName << "] not found.\n";
	} 

	return 0;
}