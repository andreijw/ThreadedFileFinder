#pragma once

#include <string>

namespace StringValidationHelper {
	using std::string;

	/**
	* @brief Check to see if the string is valid
	* 
	* @param str The string to validate
	* @return bool True if the string is valid, false otherwise
	*/
	bool isStringValid(const char* str) {
		// Check to see if the string is empty
		if (str == nullptr || str[0] == '\0') {
			return false;
		}

		// Validate that there are no wildcards in the search strings
		const char* wildcards[] = { "*", "?", "<", ">", "|", ":", "\"" };
		for (const char* wildcard : wildcards) {
			if (strstr(str, wildcard) != nullptr) {
				return false;
			}
		}

		return true;
	}
};