/**
* @file FileFinder.cpp
* 
* This file contains the main function for the FileFinder program.
* The FileFinder program is a command line utility that searches a directory for files that contain a specific search string.
* The user provides the directory to search and one or more search strings to look for in the files.
* 
* The program uses multiple threads to scan the directory in parallel. One thread is created per search string.
* 
* The user can enter commands while the program is running. The user can enter "dump" to see the results of the scan so far,
* or "exit" to stop the scan and exit the program.
* 
* The program uses the FileScanner class to perform the scanning and searching of files.
*/

#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>

#include "Constants.h"
#include "EnvironmentHelper.h"
#include "FileScanner.h"
#include "FileValidationHelper.h"
#include "StringValidationHelper.h"

using namespace std;

static bool validateArguments(int argc, char* argv[])
{
	// Ensure the user has provided the correct number of arguments. Directory and at least one substring are required.
	if (argc < 3)
	{
		cerr << "Usage: FileFinder <directory> <substring1> [<substring2> ... ]" << endl;
		return false;
	}

	// Cap the number of search strings allowed. Default value is number of cpu cores - 2. To prevent the program running out of memory.
	int maxSearchStrings = EnvironmentHelper::getMaxSearchStrings(), requestedSearchStrings = argc - 2;
	if (requestedSearchStrings > maxSearchStrings)
	{
		cerr << "Too many search strings provided. Maximum allowed is " << maxSearchStrings << " | Update the environment file or variable to change this " << endl;
		return false;
	}

	// Validate the directory path provided by the user
	if (!FileValidationHelper::isValidDirectory(argv[1]))
	{
		cerr << "Invalid directory path provided. Please provide a valid directory path." << endl;
		return false;
	}

	// Validate the search strings are valid string literals
	for (int i = 2; i < argc; ++i)
	{
		if (!StringValidationHelper::isStringValid(argv[i]))
		{
			cerr << "Invalid search string provided at position " << i << " . Please provide a valid search string." << endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!validateArguments(argc, argv)) {
		return 1;
	}

	// Start scan on new threads for each search string. Pass in argv[2]....argv[requestedSearchStrings-1] as search strings
	FileScanner::FileScanner scanner(argc - 2, argv + 2);
	if (!scanner.StartScan(argv[1]))
	{
		cerr << "Failed to start scan. Exiting program." << endl;
		return 1;
	}

	// Check for dump or exit commands. Run the blocking getline only if there is actual keyboard input
	string command;
	while (scanner.ScanRunning())
	{
		if (_kbhit()) { // Non-crossplatform call. May need to update to curses.h or have platform specific calls for this.
			getline(cin, command);
			if (command == Constants::DUMP_COMMAND)
			{
				scanner.DumpSanResults();
			}
			else if (command == Constants::EXIT_COMMAND)
			{
				scanner.StopScan();
			}
			else {
				cout << "Invalid command: " << command << endl;
			}
		}
	}
	scanner.StopScan();

	// Wait for all threads to finish
	cout << "file-scanner execution complete" << endl;
	return 0;
}
