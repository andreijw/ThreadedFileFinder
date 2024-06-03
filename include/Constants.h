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
	constexpr std::string_view CORES_ENV_VAR_NAME = "MAX_SEARCH_STRINGS";
	constexpr int MAX_FILE_PATH_LENGTH_VALUE = 256;
	constexpr std::string_view MAX_FILE_PATH_ENV_VAR_NAME = "MAX_FILE_PATH_LENGTH";
	constexpr int BATCH_INTERVAL_SECONDS = 10;
	constexpr std::string_view BATCH_INTERVAL_SECONDS_NAME = "BATCH_INTERVAL_SECONDS";
	constexpr std::string_view DUMP_COMMAND = "dump";
	constexpr std::string_view EXIT_COMMAND = "exit";
};