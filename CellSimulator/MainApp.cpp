#include "MainApp.h"
#include "Mouse.h"
#include "Environment.h"
#include <iostream>

sf::RenderWindow* MainApp::window;

sf::View MainApp::view;

sf::Font MainApp::defaultFont;

sf::VideoMode MainApp::windowVideoMode;

std::string MainApp::windowTitle;

int MainApp::_currentZoom = 0;


MainApp::~MainApp() {}

void MainApp::run(sf::RenderWindow& w)
{
	window = &w;

	configure();
	Environment::configure();



	sf::Event event;

	while (window->isOpen())
	{
		cell::Mouse::update();

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				std::clog << event.mouseWheelScroll.delta << std::endl;
				cell::Mouse::setWheelDelta(event.mouseWheelScroll.delta);
			}
		}

		//update
		updateViewCenter();
		updateViewZoom();



		window->clear();

		//draw
		Environment::draw(*window);

		window->display();
	}
}

sf::RenderWindow & MainApp::getWindowHandle()
{
	return *window;
}

sf::View & MainApp::getViewHandle()
{
	return view;
}

void MainApp::configure()
{
	windowVideoMode = sf::VideoMode(1378, 768);
	windowTitle = "Cell Simulator";

	std::clog << windowTitle << " - build " << __DATE__ << " " << __TIME__ << std::endl;

	//TODO: load font

	//TODO: load textures

	window->create(windowVideoMode, windowTitle, sf::Style::Close);

	view.setSize(sf::Vector2f(windowVideoMode.width, windowVideoMode.height));
	view.setCenter(sf::Vector2f(windowVideoMode.width / 2, windowVideoMode.height / 2));
	window->setView(view);
}

void MainApp::updateViewZoom()
{
	if (cell::Mouse::getWheelDelta() < 0)
	{
		if (_currentZoom < _maxZoom)
		{
			_currentZoom++;
			view.zoom(1.1);
		}

	}
	else if (cell::Mouse::getWheelDelta() > 0)
	{
		if (_currentZoom > _minZoom)
		{
			_currentZoom--;
			view.zoom(0.9);
		}
	}
	window->setView(view);
}

void MainApp::updateViewCenter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		if (cell::Mouse::wasRigthReleased())
		{
			view.setCenter(cell::Mouse::getPosition());
		}

	}
	else if (cell::Mouse::isRightPressed())
	{
		auto mv = cell::Mouse::getPositionShift();
		constexpr float moveFactor = -0.95f;
		view.move(sf::Vector2f{ mv.x*moveFactor, mv.y*moveFactor });
	}
}


