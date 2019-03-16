#pragma once
#include <SFML/Graphics.hpp>

class CellSimMouse;

class CellSimApp final
{
public:
	friend class CellSimMouse;

	CellSimApp() = delete;

	static void run();

	static void configure();

	static void close();

	static std::shared_ptr<sf::RenderWindow> getWindowHandle();

	static const float& getDeltaTime();

private:
	static std::shared_ptr<sf::RenderWindow> window;

	static sf::View view;

	static sf::VideoMode windowVideoMode;

	static std::string windowTitle;

	static void updateViewZoom();

	static void updateViewCenter();

	static double _currentZoom;
	static int _expectedZoom;
	static constexpr int _maxZoom = -7;
	static constexpr int _minZoom = 3;

	static float deltaTime;
};

