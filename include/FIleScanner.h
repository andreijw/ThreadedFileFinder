/**
* @file FileScanner.h
* 
* This file contains the declaration of the FileScanner class.
* The FileScanner class is responsible for scanning a directory for files that contain a specific search string
* using multiple threads to scan the directory in parallel. One thread is created per search string.
*
*/
#pragma once

#include <chrono>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <string>
#include <stop_token>
#include <thread>
#include <vector>

#include "Constants.h"
#include "EnvironmentHelper.h"

namespace FileScanner
{
	class FileScanner
	{
	public:
		FileScanner(int threadNumber, char* searchStrings[]);
		~FileScanner();

		bool StartScan(const std::string& scanDirectory);
		bool StopScan();
		bool ScanRunning() const;
		void DumpSanResults();

	private:
		int m_threadNumber;
		int m_dumpTimer;
		int m_threadsFinished;
		std::stop_source m_sharedStopSource;
		std::vector<std::string> m_searchStrings;
		std::vector<std::jthread> m_threads;
		std::vector<std::string> m_filesFound;
		std::mutex m_mutex;
		void ScanDirectory(const std::string& directory, const std::string& searchString, std::stop_source stopSource);
		void TimerDumpResults(std::stop_source stopSource);
	};
};