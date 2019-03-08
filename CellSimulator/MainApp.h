#pragma once
#include <SFML/Graphics.hpp>

class MainApp final
{
public:
	MainApp() = delete;
	~MainApp();

	static void run();

private:

	static void configure();

	static sf::RenderWindow window;

	static sf::Font defaultFont;

	static sf::VideoMode windowVideoMode;

	static std::string windowTitle;

};

