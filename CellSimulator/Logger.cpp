#include "Logger.h"
#include <iostream>
#include <string>

std::mutex Logger::logMutex;

void Logger::log(const std::string& s, bool endl)
{
	std::lock_guard<std::mutex> lock(logMutex);
	std::clog << s;
	if (endl) std::clog << std::endl;
	else std::clog << std::flush;
}
