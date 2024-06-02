#pragma once

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>
#include <iostream>

#include "Constants.h"

namespace FileScanner
{
	using std::string;
	using std::vector;
	using std::jthread;
	using std::cout;
	using std::endl;

	class FileScanner
	{
	public:
		FileScanner(int threadNumber, char* searchStrings[]);
		~FileScanner();

		bool StartScan(const string& scanDirectory);
		bool StopScan();
		void DumpSanResults();

	private:
		int m_threadNumber;
		int m_dumpTimer;
		vector<string> m_searchStrings;
		vector<jthread> m_threads;
		void CleanUp();
		void ScanDirectory(const string& directory, const string& searchString);
	};
}