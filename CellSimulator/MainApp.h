#pragma once
#include <SFML/Graphics.hpp>

class MainApp final
{
public:
	MainApp() = delete;
	~MainApp();

	static void run();
	
	static const sf::RenderWindow& getWindowHandle();

	static const sf::View& getViewHandle();

private:

	static void configure();

	static sf::RenderWindow window;

	static sf::View view;

	static sf::Font defaultFont;

	static sf::VideoMode windowVideoMode;

	static std::string windowTitle;

};

