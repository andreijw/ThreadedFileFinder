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
- Cross-platform c	++ project (created using CMake) needs testing on Linux and Mac systems. (Developed on Windows)
- The application will be run from the command line with correct permissions such as read access to the directory and files. No ACL checks are performed or needed.
- There won't be that many search strings to search for. The number of search strings will be capped at the number of CPU cores available on the system. This is to prevent the application from being too slow. If a lot of search strings are needed, then I could modify the code to have a single thread search for a batch of strings, or increase the thread cap.
- Each search string will run on a thread, if all threads complete their scan, the application will exit without needing to wait for the exit command. This is to avoid just looping forever.
- There is no need to add a "--help / -h" command line argument printing the usage of the CLI, I will focus on the more important parts of the project.
- Only basic user input validation is provided, the goal of this project is to focus on the synchronization and programming aspects of it, not the user input validation.
- Only CRT and STL libraries are used, no third-party libraries are allowed.

# Design
- The application will be a command line application that will take the directory to search as the first command line argument, followed by one or more substrings (literals, not wildcards) to search for.
- There is some basic input validation on the number of arguments, the input directory (check if it's valid), and the substrings, check if they are empty or contain wildcard characters.
- The application reads some runtime variables from an .env file to avoid having to recompile the application in order to change some of the behavior. Additionally, those values can also be set as environment variables.
- There is a cap on the maximum number of substrings to search for based on the number of cpu cores available on the system. This behavior can be modified through the environment variables.
- There is a dedicated thread to dumping the container strings on a timed interval. This value can be modified through the environment variables.
- The application runs, and performs the basic input validation, then it creates a FileScanner object and starts the scan. This creates the scan threads per search string, as well as the output dump thread.
- std::jthread objects are utilized in order to gracefully be able to interrupt the threads when the application is done. All resources are cleaned up.
- The substring check against the filename will be done with the find function instead of regex since there are no wildcard characters. For this case the performance of find is better than of regex.
- The threads will use a mutex to lock the vector of found files, this is to prevent race conditions. Each thread will lock the vector, and push back the new file found. A lock_guard is used to gracefully handle releasing the lock.
- After the scan starts, the main application waits for all the threads to finish, while waiting, it reads the user input command to see if the "exit" or "dump" commands are provided to perform the required functionality.
- The _kbhit() function is used to aid the getline() blocking function and prevent the application from blocking on user input.
- At the end  if the user provides the "exit" command, or if all the threads scanning finish, the application will gracefully exit, cleaning up all resources.
- The application was tested on Windows 10, using Visual Studio 2022, and CMake 3.28.3.

# System (Versions should probably match this or be higher)
- gcc.exe (Rev3, Built by MSYS2 project) 13.2.0
- g++.exe (Rev3, Built by MSYS2 project) 13.2.0
- CMake version 3.28.3-msvc11
- Microsoft Visual Studio Professional 2022 (64-bit) - Preview Version 17.11.0 Preview 1.1
- Windows 10

# Memory Profiling
- The memory profiling for the application was done with the Dr. Memory (Windows-only tool) 

# Build Process
- The project is built using CMake, the CMakeLists.txt file is provided in the root directory. I was building it through VS 2022, but it can also be built manually as long as you have CMake and a C++ compiler installed.
- The project is built using the following commands:
```sh
mdkir out
cd out
cmake -DCMAKE_BUILD_TYPE=Release ..
make 
#cmake --build . --config Release
```

# Tests (Not currently implemented, TBD)
- Unit testing:
	- A main test runner would be created under the tests directory. The tests would be made as functions that included assertions to check the expected behavior of the functions.
	- The following files would be automatically unit tested as part of the CI / CD process:
		- FileScanner.cpp/.h by creating a FileScanner object and testing the scan functions. (Creating directory structures with files, checking they are scanned correctly, that the file count is the correct number of files, no race conditions, stopping the scan, etc)
		- FileValidation.h - by calling the namespace functions both valid and invalid inputs.
		- EnvironmentHelper.h - by calling the namespace functions both valid and invalid inputs (Reading from environment variables, reading from the .env file, using default values if not found)
		- StringValidation.h - by calling the namespace functions both valid and invalid inputs.
  		- Mock tests to emulate the file scanner and different parts of the code
	
- Integration testing:
	- Automated Integration testing would happen for the entry point of the application, the FileFinder.cpp file.
	- A test suite of different tests would invoke the application with different parameters to check the input validation and correct failure cases.
	- Other tests would validate that the files are correctly found and outputted to the console, and test that the scanner and resources are correctly started, stopped, and disposed of.

# Improvements
- One improvement that could be made is to have a single thread search for a batch of substrings. This would be useful if there are a lot of substrings to search for. This would reduce the number of threads created and thus reduce the overhead of creating and managing threads.
- Each thread is writing and locking the vector per file found. This could be improved by having a single thread write to the vector or only writing out a batch of files per lock, this would reduce the contention on the vector and improve performance. Another approach is to use a lock-free data structure like a lock-free queue
- Fix the 1 non cross platform function _kbhit() to a cross platform solution.
- Add a file count variable to the FileScanner object to keep track of the number of files scanned, this would be useful for the dump command.
- Better test the memory pressure and look for memory leaks

# Compatibility Issues
- To easily read the user input without blocking the application, the _kbhit() function is used. This function is not part of the standard C++ library and is only available on Windows. This function would need to be replaced with a cross-platform solution to run on Linux or Mac systems.
