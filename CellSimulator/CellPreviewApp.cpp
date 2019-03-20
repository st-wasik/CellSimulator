#include "CellPreviewApp.h"
#include "MainApp.h"
#include "Logger.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

std::shared_ptr<sf::RenderWindow> CellPreviewApp::window;

sf::VideoMode CellPreviewApp::windowVideoMode;

std::string CellPreviewApp::windowTitle;

void CellPreviewApp::configure()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(350, 768 / 2 - 5);
	windowTitle = "Cell Preview";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	window->create(windowVideoMode, windowTitle, sf::Style::Titlebar);
	window->setFramerateLimit(60);
}

void CellPreviewApp::run()
{
	//tgui::Gui gui{ *window };
	sf::Event event;
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			//gui.handleEvent(event); // Pass the event to the widgets
		}

		window->clear(sf::Color(140, 140, 60));
		//gui.draw(); // Draw all widgets
		window->display();
	}
}

void CellPreviewApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> CellPreviewApp::getWindowHandle()
{
	return window;
}