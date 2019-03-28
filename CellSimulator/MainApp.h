#pragma once
#include <SFML/Graphics.hpp>
#include <atomic>
class MainApp final
{
public:
	MainApp() = delete;

	static void run();

	static void close();

	static std::atomic_bool appRun;
};

