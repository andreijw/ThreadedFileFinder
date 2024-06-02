#pragma once

#include <thread>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

#include "Constants.h"

using namespace std;

namespace EnvironmentHelper
{
	// Load the environment variables from the .env file
	map<string, string> load_env() {
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

	int get_max_search_strings() {
		int maxSearchStrings = 0;
		try {
			// First check the environment variable if set already
			auto maxSearchStringsEnv = getenv(CORES_ENV_VAR_NAME.c_str());
			if (maxSearchStringsEnv != nullptr) {
				return stoi(maxSearchStringsEnv);
			}
			// If not set, then check the .env file
			map<string, string> env = load_env();
			if (env.find(CORES_ENV_VAR_NAME) != env.end()) {
				maxSearchStrings = stoi(env[CORES_ENV_VAR_NAME]);
			}
			else {
				// If not set, then set it to the number of cpu cores - 2
				maxSearchStrings = thread::hardware_concurrency() - 2;
			}
		}
		catch (const invalid_argument& e) {
			cerr << e.what() << endl;
			maxSearchStrings = thread::hardware_concurrency() - 2;
		}
		return maxSearchStrings;
	}
};