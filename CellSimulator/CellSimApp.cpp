#include "CellSimApp.h"
#include "CellSimMouse.h"
#include "Environment.h"
#include "MainApp.h"
#include "Logger.h"
#include <iostream>

std::shared_ptr<sf::RenderWindow> CellSimApp::window;

sf::View CellSimApp::view;

sf::VideoMode CellSimApp::windowVideoMode;

std::string CellSimApp::windowTitle;

int CellSimApp::_currentZoom = 0;

float CellSimApp::deltaTime = 0;


void CellSimApp::run()
{
	Environment::configure();

	view.setCenter(sf::Vector2f(Environment::getEnvironmentSize().x / 2, Environment::getEnvironmentSize().y / 2));


	sf::Event event;
	sf::Clock deltaTimeClock;

	while (window->isOpen())
	{
		deltaTimeClock.restart();
		CellSimMouse::update();

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				CellSimMouse::setWheelDelta(event.mouseWheelScroll.delta);
			}
		}

		//update
		updateViewCenter();
		updateViewZoom();

		Environment::update();

		window->clear();

		//draw
		Environment::draw(*window);

		window->display();
		deltaTime = 0.001 * deltaTimeClock.getElapsedTime().asMicroseconds();
	}
}

void CellSimApp::configure()
{
	window = std::make_shared<sf::RenderWindow>();
	windowVideoMode = sf::VideoMode(1378, 768);
	windowTitle = "Cell Simulator";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	//TODO: load textures

	window->create(windowVideoMode, windowTitle, sf::Style::Close);
	window->setFramerateLimit(60);

	view.setSize(sf::Vector2f(windowVideoMode.width, windowVideoMode.height));
	view.setCenter(sf::Vector2f(windowVideoMode.width / 2, windowVideoMode.height / 2));
	window->setView(view);
}

void CellSimApp::close()
{
	window->close();
}

std::shared_ptr<sf::RenderWindow> CellSimApp::getWindowHandle()
{
	return window;
}

void CellSimApp::updateViewZoom()
{
	if (CellSimMouse::getWheelDelta() < 0)
	{
		if (_currentZoom < _maxZoom)
		{
			_currentZoom++;
			view.zoom(1.1);
		}

	}
	else if (CellSimMouse::getWheelDelta() > 0)
	{
		if (_currentZoom > _minZoom)
		{
			_currentZoom--;
			view.zoom(0.9);
		}
	}
	window->setView(view);
}

void CellSimApp::updateViewCenter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		if (CellSimMouse::wasRigthReleased())
		{
			view.setCenter(CellSimMouse::getPosition());
		}

	}
	else if (CellSimMouse::isRightPressed())
	{
		auto mv = CellSimMouse::getPositionShift();
		constexpr float moveFactor = -0.8f;
		view.move(sf::Vector2f{ mv.x*moveFactor, mv.y*moveFactor });
	}
}

