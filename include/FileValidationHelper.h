#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include "Constants.h"

using std::string;
namespace filesystem = std::filesystem;

namespace FileValidationHelper {
	bool is_valid_directory(const string& dir_path) {
		return filesystem::exists(dir_path) && filesystem::is_directory(dir_path) && dir_path.size() <= MAX_FILE_PATH_LENGTH;
	}
};