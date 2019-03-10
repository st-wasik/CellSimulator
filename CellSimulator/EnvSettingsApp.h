#pragma once
#include <SFML/Graphics.hpp>
class EnvSettingsApp
{
public:
	EnvSettingsApp() = delete;

	static void configure();

	static void run();

	static void close();

	static std::shared_ptr<sf::RenderWindow> getWindowHandle();

private:
	static std::shared_ptr<sf::RenderWindow> window;

	static sf::VideoMode windowVideoMode;

	static std::string windowTitle;
};

