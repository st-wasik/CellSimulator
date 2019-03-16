#pragma once
#include <mutex>
class Logger
{
public:
	Logger() = delete;

	template <typename T>
	static void log(const T& t, bool endl = true)
	{
		std::lock_guard<std::mutex> lock(logMutex);
		std::clog << t;
		if (endl)
			std::clog << std::endl;
		else
			std::clog << std::flush;
	}

private:
	static std::mutex logMutex;
};

