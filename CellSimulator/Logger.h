#pragma once
#include <mutex>
class Logger
{
public:
	Logger() = delete;

	static void log(const std::string&, bool = true);
private:
	static std::mutex logMutex;
};

