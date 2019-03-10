#include "Logger.h"
#include <iostream>
#include <string>

std::mutex Logger::logMutex;

void Logger::log(const std::string& s)
{
	std::lock_guard<std::mutex> lock(logMutex);
	std::clog << s << std::endl;
}
