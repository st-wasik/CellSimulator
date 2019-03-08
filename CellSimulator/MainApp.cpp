#include "MainApp.h"


sf::RenderWindow MainApp::window;

sf::Font MainApp::defaultFont;

sf::VideoMode MainApp::windowVideoMode;

std::string MainApp::windowTitle;


MainApp::~MainApp() {}

void MainApp::run()
{
	configure();
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}





		window.clear();
		window.display();
	}
}

void MainApp::configure()
{
	windowVideoMode = sf::VideoMode(800, 600);
	windowTitle = "Cell Simulator";

	//TODO: load font

	window.create(windowVideoMode, windowTitle, sf::Style::Close);
}


