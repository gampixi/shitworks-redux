#pragma once
#include <cstdlib>
#include <string>
#include <sstream>

#define SWLOG(...) sw_Log(__LINE__, __FILE__, __VA_ARGS__)
template <typename ...Args>
static void sw_Log(int line, const char* fileName, Args&& ...args) {
	std::ostringstream stream;
	stream << fileName << "(" << line << ") : ";
	(stream << ... << std::forward<Args>(args)) << '\n';
	printf(stream.str().c_str());
}