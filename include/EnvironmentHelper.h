/**
* 
* @file EnvironmentHelper.h
* 
* This file contains the helper functions to load the environment variables and read the config values.
* 
*/
#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <thread>

#include "Constants.h"

namespace EnvironmentHelper
{
	/**
	* @brief Load the environment variables from the.env file
	* 
	* @return map<string, string> containing the environment variables
	*/
	inline std::map<std::string, std::string> loadEnv() {
		std::map<std::string, std::string> env;
		try {
			std::string line;
			std::ifstream envFile(".env");

			while (std::getline(envFile, line)) {
				std::string key = line.substr(0, line.find("="));
				std::string value = line.substr(line.find("=") + 1);
				env[key] = value;
			}
		}
		// Catch any exceptions that occur while reading the file, return variables loaded so far
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
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
	inline T getConfigValue(const std::string& configName, T defaultValue) {
		try {
			// First check the environment variable if set already
			auto configValueEnv = getenv(configName.c_str());
			if (configValueEnv != nullptr) {
				if constexpr (std::is_same<T, int>::value) {
					return std::stoi(configValueEnv);
				}
				else if constexpr (std::is_same<T, std::string>::value) {
					return std::string(configValueEnv);
				}
				else {
					return static_cast<T>(configValueEnv);
				}
			}
			// If not set, then check the .env file
			std::map<std::string, std::string> env = loadEnv();
			if (env.find(configName) != env.end()) {
				if constexpr (std::is_same<T, int>::value) {
					return std::stoi(env[configName]);
				}
				else if constexpr (std::is_same<T, std::string>::value) {
					return std::string(env[configName]);
				}
				else {
					return static_cast<T>(env[configName]);
				}
			}
		}
		catch (const std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
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
		return std::max(1, getConfigValue<int>(std::string(Constants::CORES_ENV_VAR_NAME).c_str(), (int)(std::thread::hardware_concurrency() - 2)));
	}

	/**
	* @brief Read the config value "BATCH_INTERVAL_SECONDS_NAME" from the environment variables
	* 
	* @return int value from the environment variables. Defaults to 10 seconds;
	*/
	inline int getBatchIntervalTimer() {
		return std::max(1, getConfigValue<int>(std::string(Constants::BATCH_INTERVAL_SECONDS_NAME).c_str(), Constants::BATCH_INTERVAL_SECONDS));
	}
};