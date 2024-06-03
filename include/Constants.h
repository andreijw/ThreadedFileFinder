/**
* 
* @file Constants.h
 * This file contains the constants used in the program.
 *
 * This file contains the constants used in the program.
 *
*/
#pragma once

#include <string>

namespace Constants{
	using std::string;

	const string CORES_ENV_VAR_NAME = "MAX_SEARCH_STRINGS";
	const int MAX_FILE_PATH_LENGTH_VALUE = 256;
	const string MAX_FILE_PATH_ENV_VAR_NAME = "MAX_FILE_PATH_LENGTH";
	const int BATCH_INTERVAL_SECONDS = 10; // 15 seconds
	const string BATCH_INTERVAL_SECONDS_NAME = "BATCH_INTERVAL_SECONDS";
	const string DUMP_COMMAND = "dump";
	const string EXIT_COMMAND = "exit";
};