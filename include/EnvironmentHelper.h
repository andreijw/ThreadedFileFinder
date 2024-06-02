#pragma once

#include <thread>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

#include "Constants.h"

namespace EnvironmentHelper
{
	using std::string;
	using std::map;
	using std::ifstream;
	using std::getline;
	using std::cerr;
	using std::exception;
	using std::endl;
	using std::stoi;
	using std::thread;
	using std::invalid_argument;
	using std::max;

	/**
	* Load the environment variables from the.env file
	* 
	* @return map<string, string> containing the environment variables
	*/
	map<string, string> loadEnv() {
		map<string, string> env;
		try {
			string line;
			ifstream envFile(".env");

			while (getline(envFile, line)) {
				string key = line.substr(0, line.find("="));
				string value = line.substr(line.find("=") + 1);
				env[key] = value;
			}
		}
		// Catch any exceptions that occur while reading the file, return variables loaded so far
		catch (const exception& e) {
			cerr << e.what() << endl;
		}
		return env;
	}

	/**
	* Read the config value "MAX_SEARCH_STRINGS" from the environment variables
	*
	* @return int value from the environment variables. Defaults to cpu count in system - 2;
	*/
	int getMaxSearchStrings() {
		try {
			// First check the environment variable if set already
			auto maxSearchStringsEnv = getenv(Constants::CORES_ENV_VAR_NAME.c_str());
			if (maxSearchStringsEnv != nullptr) {
				return max(1, stoi(maxSearchStringsEnv));
			}
			// If not set, then check the .env file
			map<string, string> env = loadEnv();
			if (env.find(Constants::CORES_ENV_VAR_NAME) != env.end()) {
				return max(1, stoi(env[Constants::CORES_ENV_VAR_NAME]));
			}
		}
		catch (const invalid_argument& e) {
			cerr << e.what() << endl;
		}

		// If not set, then set it to the number of cpu cores - 2
		return max(1, (int)(thread::hardware_concurrency() - 2));
	}
};