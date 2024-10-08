/**
* @file FileValidationHelper.h
* 
* This file contains some helper validation functions for file paths and directories.
* 
*/
#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#include "Constants.h"


namespace FileValidationHelper {
	/**
	* @brief Read the config value "MAX_FILE_PATH_LENGTH" from the environment variables
	*
	* @return int value from the environment variables. Defaults to 256;
	*/
	int getMaxFilePath() {
		return Constants::MAX_FILE_PATH_LENGTH_VALUE;
	}

	/** 
	* @brief Determine if the input directory is valid
	* 
	* @param dir_path The path to the directory to validate
	* @return bool true if the directory exists and is a valid directory, false otherwise
	*/
	bool isValidDirectory(const std::string& dir_path) {
		int max_file_path_length = getMaxFilePath();
		return std::filesystem::exists(dir_path) && std::filesystem::is_directory(dir_path) && dir_path.size() <= max_file_path_length;
	}
};