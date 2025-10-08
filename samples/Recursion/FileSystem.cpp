#include <iostream>			// for std::cout and std::cerr
#include <filesystem>		// stod std::filesystem library (C++17+) 
#include <cstdint>			// for std::uintmax_t type (safe integer for large sizes)

// Give std::filesystem a shorter alias for readability. 
namespace fs = std::filesystem; 

/*
	Recursively calculates total disk usage (in bytes) 
	for a given file or directory path.

	- If the path is a regular file, return its size 
	- If the path is a directory, recurse into each child entry. 
	- Prints a line for each path similar to the 'du' command in Unix. 
*/

std::uintmax_t diskUsage(const fs::path& root) {
	// total ;will accululate size of this file or directory and all children.
	std::uintmax_t total = 0; 

	try
	{
		// Case 1: If the path points to a regular file (not a folder) 
		if (fs::is_regular_file(root)) {
			total = fs::file_size(root); 
		}
		// Case 2: If the path is a directory, recurse through its contents. 
		else if (fs::is_directory(root)) {
			// Iterate through each entry (file or folder) inside this directory
			for (const auto& entry : fs::recursive_directory_iterator(root)) {
				// Recursively call disUsage() for each child.
				total += diskUsage(entry.path()); 
			}
		}
		// Print the total size (so far) and the path, like "du" output: 
		// e.g., "4096		./src"
	}
	// Catch any filesystem errors (e.g., permission denied, missing file, etc.)
	catch (const fs::filesystem_error& e)
	{
		std::cerr << "Error accessing " << root << ": " << e.what() << '\n';
	}

	// return the total size for this path (used by the parent recursion call). 
	return total; 
}

int main() {
	// define a starting point for measuring disk usage. 
	// the "." means "current directory" 
	fs::path rootPath = "."; 

	// Show which path we're analyzing (resolved to an absolute path) 
	std::cout << "Calculating disk usage for: " << fs::absolute(rootPath) << "\n\n";

	// Start the recursive computation 
	std::uintmax_t totalBytes = diskUsage(rootPath); 

	// Print a summary total at the end 
	std::cout << "\nTotal: " << totalBytes << " bytes\n"; 

	return 0; // normal program exit. 
}