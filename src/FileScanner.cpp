#include "FileScanner.h"

namespace FileScanner {
	/**
	* @brief Constructor for the FileScanner object
	* @param threadNumber The number of threads to use for the scan
	* @param searchStrings The search strings to use for the scan
	*/
	FileScanner::FileScanner(int threadNumber, char* searchStrings[])
	{
		m_threadNumber = threadNumber;
		for (int i = 0; i < threadNumber; ++i)
		{
			m_searchStrings.push_back(searchStrings[i]);
		}
		m_dumpTimer = Constants::BATCH_INTERVAL;
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
	bool FileScanner::StartScan(string scanDirectory)
	{
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