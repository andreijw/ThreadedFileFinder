/**
* 
* @file EnvironmentHelper.h
* 
* This file contains the helper functions to load the environment variables and read the config values.
* 
*/
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
	using std::is_same;

	/**
	* @brief Load the environment variables from the.env file
	* 
	* @return map<string, string> containing the environment variables
	*/
	inline map<string, string> loadEnv() {
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
	* @brief Read the config value from the environment variables, then .env file or default value
	* 
	* @param configName The name of the config value to read
	* @param defaultValue The default value to use if the config value is not set
	* @return T value from the environment variables or default value
	*/
	template<typename T>
	inline T getConfigValue(const string& configName, T defaultValue) {
		try {
			// First check the environment variable if set already
			auto configValueEnv = getenv(configName.c_str());
			if (configValueEnv != nullptr) {
				if constexpr (is_same<T, int>::value) {
					return stoi(configValueEnv);
				}
				else {
					return static_cast<T>(configValueEnv);
				}
			}
			// If not set, then check the .env file
			map<string, string> env = loadEnv();
			if (env.find(configName) != env.end()) {
				if constexpr (std::is_same<T, int>::value) {
					return stoi(env[configName]);
				}
				else {
					return static_cast<T>(env[configName]);
				}
			}
		}
		catch (const invalid_argument& e) {
			cerr << e.what() << endl;
		}

		// If not set, then set it to the default value
		return defaultValue;
	}

	/**
	* @brief Read the config value "MAX_SEARCH_STRINGS" from the environment variables
	*
	* @return int value from the environment variables. Defaults to cpu count in system - 2;
	*/
	inline int getMaxSearchStrings() {
		return max(1, getConfigValue<int>(Constants::CORES_ENV_VAR_NAME, (int)(thread::hardware_concurrency() -2)));
	}

	/**
	* @brief Read the config value "BATCH_INTERVAL_SECONDS_NAME" from the environment variables
	* 
	* @return int value from the environment variables. Defaults to 10 seconds;
	*/
	inline int getBatchIntervalTimer() {
		return max(1, getConfigValue<int>(Constants::BATCH_INTERVAL_SECONDS_NAME, Constants::BATCH_INTERVAL_SECONDS));
	}
};