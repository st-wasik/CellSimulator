#include "MainApp.h"
#include "Mouse.h"


sf::RenderWindow MainApp::window;

sf::View MainApp::view;

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
		cell::Mouse::update();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}
}

const sf::RenderWindow & MainApp::getWindowHandle()
{
	return window;
}

const sf::View & MainApp::getViewHandle()
{
	return view;
}

void MainApp::configure()
{
	windowVideoMode = sf::VideoMode(800, 600);
	windowTitle = "Cell Simulator";

	//TODO: load font

	//TODO: load textures

	window.create(windowVideoMode, windowTitle, sf::Style::Close);

	view.setSize(sf::Vector2f(windowVideoMode.width, windowVideoMode.height));
	view.setCenter(sf::Vector2f( windowVideoMode.width/2, windowVideoMode.height/2 ));
	window.setView(view);
}


