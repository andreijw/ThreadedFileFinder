/**
* @file FileScanner.cpp
* 
* This file contains the implementation of the FileScanner class.
* see FileScanner.h for more details.
* 
*/
#include "FileScanner.h"

namespace FileScanner {
	/**
	* @brief Constructor for the FileScanner object
	* 
	* @param threadNumber The number of threads to use for the scan
	* @param searchStrings The search strings to use for the scan
	*/
	FileScanner::FileScanner(int threadNumber, char* searchStrings[]) : m_threadNumber(threadNumber), m_threadsFinished(0)
	{
		m_dumpTimer = EnvironmentHelper::getBatchIntervalTimer();
		;
		for (int i = 0; i < threadNumber; ++i)
		{
			// Allocate space in the system, but don't actually start the threads. This will be done in the StartScan function
			m_searchStrings.push_back(searchStrings[i]);
		}
		m_threads.reserve(threadNumber);
	}

	/**
	* @brief Destructor for the FileScanner object. Cleans up any resources used by the object
	*/
	FileScanner::~FileScanner()
	{
		m_searchStrings.clear();
		m_filesFound.clear();
		for (auto& thread : m_threads)
		{
			thread.join();
		}
		m_threads.clear();
	}

	/**
	* @brief Start the scan on the provided directory
	 *
	 * @param scanDirectory The directory to scan
	 * @return bool True if the scan was started successfully, false otherwise
	*/
	bool FileScanner::StartScan(const string& scanDirectory)
	{
		cout << "Starting scan on path: " << scanDirectory << endl;
		try {
			for (int i = 0; i < m_threadNumber; ++i)
			{
				m_threads.push_back(jthread(&FileScanner::ScanDirectory, this, scanDirectory, m_searchStrings[i], m_sharedStopSource));
			}
			int x = m_threads.size();
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		return false;
	}

	/**
	* @brief Stop the scan
	 *
	 * @return bool True if the scan was stopped successfully, false otherwise
	*/
	bool FileScanner::StopScan()
	{
		try {
			m_sharedStopSource.request_stop();
			DumpSanResults();
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
	}

	/**
	* @brief Scan the provided directory for the search string
	 *
	 * @param directory The directory to scan
	 * @param searchString The search string to look for
	*/
	void FileScanner::ScanDirectory(const string& directory, const string& searchString, std::stop_source stopSource)
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
			if (stopSource.get_token().stop_requested()) {
				break;
			}
			if (entry.is_regular_file()) {
				string fileName = entry.path().filename().string();
				if (fileName.find(searchString) != string::npos) { // Find is faster and simpler than regex for simple string matching
					lock_guard<mutex> lock(m_mutex);
					m_filesFound.push_back(entry.path().string());
				}
			}
		}
		lock_guard<mutex> lock(m_mutex);
		++m_threadsFinished;
	}

	/**
	* @brief Check if the scan is running
	 *
	 * @return bool True if the scan is running, false otherwise
	*/
	bool FileScanner::ScanRunning() const
	{
		return m_threadsFinished != m_threadNumber;
	}

	/**
	* @brief Dump the results of the scan to the console
	*/
	void FileScanner::DumpSanResults()
	{
		lock_guard<mutex> lock(m_mutex);
		for (const auto& file : m_filesFound)
		{
			cout << "Found file: " << file << endl;
		}
		m_filesFound.clear();
	}
}