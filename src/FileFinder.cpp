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
	int maxSearchStrings = EnvironmentHelper::get_max_search_strings();
	if ((argc - 2) > maxSearchStrings)
	{
		cout << "Too many search strings provided. Maximum allowed is " << maxSearchStrings <<  " | Update the environment file or variable to change this " << endl;
		return 1;
	}

	// Validate the directory path provided by the user
	if (!FileValidationHelper::is_valid_directory(argv[1]))
	{
		cout << "Invalid directory path provided. Please provide a valid directory path." << endl;
		return 1;
	}


	cout << "Hello CMake." << endl;
	return 0;
}
