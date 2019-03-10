#include "EnvSettingsApp.h"
#include "MainApp.h"
#include "Logger.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

std::shared_ptr<sf::RenderWindow> EnvSettingsApp::window;

sf::VideoMode EnvSettingsApp::windowVideoMode;

std::string EnvSettingsApp::windowTitle;

void EnvSettingsApp::configure()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(350, 768/2 - 5);
	windowTitle = "Environment Settings";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	window->create(windowVideoMode, windowTitle, sf::Style::Titlebar);
	window->setFramerateLimit(60);
}

void EnvSettingsApp::run()
{
	tgui::Gui gui{ *window };
	sf::Event event;
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			gui.handleEvent(event); // Pass the event to the widgets
		}

		window->clear(sf::Color(140, 140, 60));
		gui.draw(); // Draw all widgets
		window->display();
	}
}

void EnvSettingsApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> EnvSettingsApp::getWindowHandle()
{
	return window;
}
