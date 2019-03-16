#pragma once
#include <string>
#include<SFML/Graphics.hpp>
class CellListApp
{
public:
	CellListApp() = delete;

	static void configure();

	static void run();

	static void close();

	static std::shared_ptr<sf::RenderWindow> getWindowHandle();

private:
	static std::shared_ptr<sf::RenderWindow> window;

	static sf::VideoMode windowVideoMode;

	static std::string windowTitle;
};
