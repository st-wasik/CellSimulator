#pragma once
#include <SFML/Graphics.hpp>

class MainApp final
{
public:
	MainApp() = delete;
	~MainApp();

	static void run(sf::RenderWindow& window);
	
	static sf::RenderWindow& getWindowHandle();

	static sf::View& getViewHandle();

private:

	static void configure();

	static sf::RenderWindow* window;

	static sf::View view;

	static sf::Font defaultFont;

	static sf::VideoMode windowVideoMode;

	static std::string windowTitle;

	static void updateViewZoom();

	static void updateViewCenter();

	static int _currentZoom;
	static constexpr int _maxZoom = 10;
	static constexpr int _minZoom = -7;

	static float deltaTime;

};

