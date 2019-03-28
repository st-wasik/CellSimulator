#include "CellListApp.h"
#include "MainApp.h"
#include "Logger.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

CellListApp::CellListApp()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(768, 150);
	windowTitle = "Cell List";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	window->create(windowVideoMode, windowTitle, sf::Style::Titlebar);
	window->setFramerateLimit(60);

	gui = std::make_shared<tgui::Gui>(*window);

	theme.load("../../CellSimulator/TGUI-0.8/themes/TransparentGrey.txt");
}

CellListApp::~CellListApp()
{
}

void CellListApp::configure()
{
}

CellListApp & CellListApp::getInstance()
{
	static CellListApp instance;
	return instance;
}

void CellListApp::update()
{
	sf::Event event;
	if (window->isOpen())
	{
		if (!MainApp::appRun)
		{
			window->close();
		}

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			gui->handleEvent(event); // Pass the event to the widgets
		}

		window->clear(sf::Color(140, 140, 60));
		gui->draw(); // Draw all widgets
		window->display();
	}
}

void CellListApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> CellListApp::getWindowHandle()
{
	return window;
}

