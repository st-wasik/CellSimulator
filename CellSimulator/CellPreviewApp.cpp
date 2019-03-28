#include "CellPreviewApp.h"
#include "MainApp.h"
#include "Logger.h"
#include <TGUI/TGUI.hpp>
#include <iostream>

CellPreviewApp::CellPreviewApp()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(350, 768 / 2 - 5);
	windowTitle = "Cell Preview";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	window->create(windowVideoMode, windowTitle, sf::Style::Titlebar);
	window->setFramerateLimit(60);

	gui = std::make_shared<tgui::Gui>(*window);

	theme.load("../../CellSimulator/TGUI-0.8/themes/TransparentGrey.txt");
}


CellPreviewApp::~CellPreviewApp()
{
}

CellPreviewApp & CellPreviewApp::getInstance()
{
	static CellPreviewApp instance;
	return instance;
}

void CellPreviewApp::configure()
{

}

void CellPreviewApp::update()
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

void CellPreviewApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> CellPreviewApp::getWindowHandle()
{
	return window;
}
