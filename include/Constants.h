#pragma once

#include <string>

namespace Constants{
	using std::string;

	const string CORES_ENV_VAR_NAME = "MAX_SEARCH_STRINGS";
	const int MAX_FILE_PATH_LENGTH_VALUE = 256;
	const string MAX_FILE_PATH_ENV_VAR_NAME = "MAX_FILE_PATH_LENGTH";
	const int BATCH_INTERVAL = 15; // 15 seconds
	const string DUMP_CPMMAND = "dump";
	const string EXIT_COMMAND = "exit";
};