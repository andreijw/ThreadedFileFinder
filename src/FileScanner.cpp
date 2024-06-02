#include "FileScanner.h"

namespace FileScanner {
	/**
	* @brief Constructor for the FileScanner object
	* @param threadNumber The number of threads to use for the scan
	* @param searchStrings The search strings to use for the scan
	*/
	FileScanner::FileScanner(int threadNumber, char* searchStrings[])
	{
		m_dumpTimer = Constants::BATCH_INTERVAL;
		m_threadNumber = threadNumber;
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
		CleanUp();
	}

	/**
	* @brief Start the scan on the provided directory
	 *
	 * @param scanDirectory The directory to scan
	 * @return bool True if the scan was started successfully, false otherwise

	*/
	bool FileScanner::StartScan(const string& scanDirectory)
	{
		try {
			for (int i = 0; i < m_threadNumber; ++i)
			{
				m_threads.push_back(jthread(&FileScanner::ScanDirectory, this, scanDirectory, m_searchStrings[i]));
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
		return false;
	}

	/**
	* @brief Scan the provided directory for the search string
	 *
	 * @param directory The directory to scan
	 * @param searchString The search string to look for

	*/
	void FileScanner::ScanDirectory(const string& directory, const string& searchString)
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
			if (entry.is_regular_file()) {
				string fileName = entry.path().filename().string();
				if (fileName.find(searchString) != string::npos) { // Find is faster and simpler than regex for simple string matching
					cout << "Found file: " << entry.path() << endl;
				}
			}
		}
	}

	/**
	* @brief Dump the results of the scan to the console
	*/
	void FileScanner::DumpSanResults()
	{
	}

	/**
	* @brief Clean up the FileScanner object
	 *
	 *
	*/
	void FileScanner::CleanUp()
	{
		m_searchStrings.clear();
	}
}