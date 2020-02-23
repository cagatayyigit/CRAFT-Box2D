#pragma once
#include <iostream>

namespace debug {
	void log(std::string str) {
		std::cout << "[LOG] " << str << std::endl;
	}
}