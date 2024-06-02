#pragma once

#include <string>
#include <vector>

#include "Constants.h"

namespace FileScanner
{
	using std::string;
	using std::vector;

	class FileScanner
	{
	public:
		FileScanner(int threadNumber, char* searchStrings[]);
		~FileScanner();

		bool StartScan(string scanDirectory);
		bool StopScan();
		void DumpSanResults();

	private:
		int m_threadNumber;
		int m_dumpTimer;
		vector<string> m_searchStrings;
		void CleanUp();
	};
}