#pragma once
#include <iostream>

namespace debug {
	void log(std::string str) {
		std::cout << "[LOG] " << str << std::endl;
	}

	void log_progress(std::string str, std::string progress) {
		std::cout << "[LOG] " << str << " " << progress <<  "\r";
	}
}