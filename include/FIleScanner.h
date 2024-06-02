/**
* @file FileScanner.h
* 
* This file contains the declaration of the FileScanner class.
* The FileScanner class is responsible for scanning a directory for files that contain a specific search string
* using multiple threads to scan the directory in parallel. One thread is created per search string.
*
*/
#pragma once

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <mutex>

#include "Constants.h"

namespace FileScanner
{
	using std::string;
	using std::vector;
	using std::jthread;
	using std::cout;
	using std::endl;
	using std::mutex;
	using std::lock_guard;

	class FileScanner
	{
	public:
		FileScanner(int threadNumber, char* searchStrings[]);
		~FileScanner();

		bool StartScan(const string& scanDirectory);
		bool StopScan();
		bool ScanRunning() const;
		void DumpSanResults();

	private:
		int m_threadNumber;
		int m_dumpTimer;
		bool m_scanRunning;
		vector<string> m_searchStrings;
		vector<jthread> m_threads;
		vector<string> m_filesFound;
		mutex m_mutex;
		void ScanDirectory(const string& directory, const string& searchString);
	};
}