# Sensor SDE Coding Project
Sensor SDE Coding Project

# Problem Statement
You are to write a command line application that searches a directory tree (i.e. - including
subdirectories) for filenames that contain anywhere in them a specified substring.
The application takes the directory to search as the first command line argument, followed by
one or more substrings (literals, not wildcards) to search for.
file-finder <dir> <substring1>[<substring2> [<substring3>]...]

# Assumptions
- C++20 is used for the project mainly for the jthread interruptible objects
- Cross platform c++ project (created using cmake) some testing needs to be done on Linux and mac systems
- The application will be run from the command line with correct permissions.
- The application will run with read access to the directory and files. No ACL checks are performed.
- There won't be that many search strings to search for. The number of search strings will be capped at the number of cpu cores available on the system. This is to prevent the application from being too slow. If a lot of search strings are needed, then I could modify the code to have a single thread search for a batch of strings, or increase the thread cap.

# Design
- The application will be a command line application that will take the directory to search as the first command line argument, followed by one or more substrings (literals, not wildcards) to search for.
- Perform some basic input validation on the number of arguments, the input directory (check if it's valid), and the substrings.
- Cap the maximum number of substrings to search for based on the number of cpu cores available on the system. There is an optional .env file that allows the user to override this value.
- Create threads equal to the number of substrings to search for. Each thread will search for a substring in the directory tree. I will use std::jthread for the threads to allow for interruption.
- The substring check will be done with find since there are no wildcard characters and thus there is no need to use regex. The performance of find is better than of regex.

# Build Process

# Tests

# Improvements
- One improvement that could be made is to have a single thread search for a batch of substrings. This would be useful if there are a lot of substrings to search for. This would reduce the number of threads created and thus reduce the overhead of creating and managing threads.
- Each thread is writing and locking the vector per file found. This could be improved by having a single thread write to the vector or only writing out a batch of files per lock, this would reduce the contention on the vector and improve performance. Another approach is to use a lock free data structure like a lock free queue