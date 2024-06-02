// FileFinder.cpp : Defines the entry point for the application.
//

#include "FileFinder.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Ensure the user has provided the correct number of arguments. Directory and at least one substring are required.
	if (argc < 3)
	{
		cout << "Usage: FileFinder <directory> <substring1> [<substring2> ... ]" << endl;
		return 1;
	}

	// Cap the number of search strings allowed. Default value is number of cpu cores - 2. To prevent the program running out of memory.
	int maxSearchStrings = EnvironmentHelper::getMaxSearchStrings();
	int requestedSearchStrings = argc - 2;
	if (requestedSearchStrings > maxSearchStrings)
	{
		cout << "Too many search strings provided. Maximum allowed is " << maxSearchStrings <<  " | Update the environment file or variable to change this " << endl;
		return 1;
	}

	// Validate the directory path provided by the user
	if (!FileValidationHelper::isValidDirectory(argv[1]))
	{
		cout << "Invalid directory path provided. Please provide a valid directory path." << endl;
		return 1;
	}

	// Validate the search strings are valid string literals
	for (int i = 2; i < argc; ++i)
	{
		if (!StringValidationHelper::isStringValid(argv[i]))
		{
			cout << "Invalid search string provided at position " << i << " . Please provide a valid search string." << endl;
			return 1;
		}
	}

	// Start scan on new threads
	FileScanner::FileScanner scanner(requestedSearchStrings, argv + 2);
	if (!scanner.StartScan(argv[1]))
	{
		cout << "Failed to start scan. Exiting program." << endl;
		return 1;
	}

	// Check for dump or exit commands

	// Wait for all threads to finish

	cout << "Hello CMake." << endl;
	return 0;
}
