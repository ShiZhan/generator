#ifndef options_h
#define options_h
#include <string>
#include <sstream>
#include <algorithm>

namespace opt {
	char* getOption(char** begin, char** end, const std::string& option) {
		char ** itr = std::find(begin, end, option);
		if (itr != end && ++itr != end) return *itr;
		return 0;
	}

	bool chkOption(char** begin, char** end, const std::string& option) {
		return std::find(begin, end, option) != end;
	}

	template <typename T>
	T getValue(char** begin, char** end, const std::string& option, T d) {
		T value = d;
		char* str = getOption(begin, end, option);
		if (str) {
			try {
				std::stringstream(str) >> value;
			} catch(std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
		return value;
	}
}
#endif
