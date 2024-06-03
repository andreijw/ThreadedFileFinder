# Sensor SDE Coding Project
Sensor SDE Coding Project

# Problem Statement
You are to write a command line application that searches a directory tree (i.e. - including subdirectories) for filenames that contain anywhere in them a specified substring.
The application takes the directory to search as the first command line argument, followed by one or more substrings (literals, not wildcards) to search for:
```sh
file-finder <dir> <substring1>[<substring2> [<substring3>]...]
```

# Assumptions
- C++20 is used for the project mainly for the jthread interruptible objects
- Cross platform c	++ project (created using CMake) some testing needs to be done on Linux and mac systems. (Developed on Windows)
- The application will be run from the command line with correct permissions such as read access to the directory and files. No ACL checks are performed or needed.
- There won't be that many search strings to search for. The number of search strings will be capped at the number of cpu cores available on the system. This is to prevent the application from being too slow. If a lot of search strings are needed, then I could modify the code to have a single thread search for a batch of strings, or increase the thread cap.
- Each search string will run on a thread, if all threads complete their scan, the application will exit without needing to wait for the exit command. This is to avoid just looping forever.
- There is no need to add a "--help / -h" command line argument printing the usage of the cli, I will focus on the more important parts of the project.
- Only basic user input validation is provided, the goal of this project is to focus on the synchronization and programming aspects of it, not the user input validation.
- Only CRT and STL libraries are used, no third party libraries are allowed.

# Design
- The application will be a command line application that will take the directory to search as the first command line argument, followed by one or more substrings (literals, not wildcards) to search for.
- There is some basic input validation on the number of arguments, the input directory (check if it's valid), and the substrings, check if they are empty or contain wildcard characters.
- The application reads some runtime variables from an .env file to avoid having to recompile the application in order to change some of the behavior. Additionally those values can also be set as environment variables.
- There is a cap on the maximum number of substrings to search for based on the number of cpu cores available on the system. This behavior can be modified through the environment variables.
- There is a dedicated thread to dumping the container strings on a timed interval. This value can be modified through the environment variables.
- The application runs, and performs the basic input validation, then it creates a FileScanner object and starts the scan. This creates the scan threads per search string, as well as the output dump thread.
- std::jthread objects are utilized in order to gracefully be able to interrupt the threads when the application is done. All resources are cleaned up.
- The substring check against the filename will be done with the find function instead of regex since there are no wildcard characters. For this case the performance of find is better than of regex.
- The threads will use a mutex to lock the vector of found files, this is to prevent race conditions. Each thread will lock the vector, and push back the new file found. A lock_guard is used to gracefully handle releasing the lock.
- After the scan starts, the main application waits for all the threads to finish, while waiting, it reads the user input command to see if the "exit" or "dump" commands are provided in order to perform the required functionality.
- The kbhit() function is used to aid the getline() blocking function and avoid the application from blocking on user input.
- At the end  if the user provides the "exit" command, or if all the threads scanning finish, the application will gracefully exit, cleaning up all resources.
- The application was tested on Windows 10, using Visual Studio 2022, and CMake 3.28.3.

# Memory Profiling

# Build Process

# Tests (No required as part of the assignment)
- Unit testing:
	- A main test runner would be created under the tests directory. The tests would be created as functions that included asserts to check the expected behavior of the functions.
	- The following files would be automatically unit tested as part of the CI / CD process:
		- FileScanner.cpp/.h by creating a FileScanner object and testing the scan functions
		- FileValidation.h - by calling the namespace functions
		- EnvironmentHelper.h - by calling the namespace functions
		- StringValidation.h - by calling the namespace functions
	
- Integration testing:
	- Automated Integration testing would happen for the entry point of the application, the FileFinder.cpp file.
	- There would be a test suite of different tests that would invoke the application with different parameters to check the input validation and correct failure cases.
	- Other tests would validate that the files are correctly found and outputted to the console, and testing that the scanner and resources are correctly started, stoped and disposed of.

# Improvements
- One improvement that could be made is to have a single thread search for a batch of substrings. This would be useful if there are a lot of substrings to search for. This would reduce the number of threads created and thus reduce the overhead of creating and managing threads.
- Each thread is writing and locking the vector per file found. This could be improved by having a single thread write to the vector or only writing out a batch of files per lock, this would reduce the contention on the vector and improve performance. Another approach is to use a lock free data structure like a lock free queue