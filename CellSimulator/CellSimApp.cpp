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

double CellSimApp::_currentZoom = 0;

int CellSimApp::_expectedZoom = 0;

float CellSimApp::deltaTime = 0;


void CellSimApp::run()
{

	//getting instance configures environment for first use
	Environment::getInstance();

	view.setCenter(sf::Vector2f(Environment::getInstance().getSize().x / 2, Environment::getInstance().getSize().y / 2));

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
				CellSimMouse::setWheelDelta(event.mouseWheelScroll.delta);
		}


		//update
		updateViewCenter();
		updateViewZoom();

		Environment::getInstance().update();

		window->clear();

		//draw
		Environment::getInstance().draw(*window);

		window->display();
		deltaTime = 0.0001 * deltaTimeClock.getElapsedTime().asMicroseconds();
		//Logger::log("FPS " + std::to_string(1/deltaTime*100) + "\r", false);
		//Logger::log(std::to_string(deltaTime) + "\r", false);
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
	//window->setVerticalSyncEnabled(true);

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

const float & CellSimApp::getDeltaTime()
{
	return deltaTime;
}

void CellSimApp::updateViewZoom()
{
	//std::cout << "Min: "<<_minZoom << "  Max: " << _maxZoom << "  Exp: " << _expectedZoom << "  Curr: " << _currentZoom << std::endl;

	if (CellSimMouse::getWheelDelta() < 0)
	{
		if (_expectedZoom < _minZoom)
			_expectedZoom+=2;
	}
	else if (CellSimMouse::getWheelDelta() > 0)
	{
		if (_expectedZoom >  _maxZoom)
			_expectedZoom-=2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) && window->hasFocus()) _expectedZoom = 0;

	if (_currentZoom < _expectedZoom && abs(_currentZoom - _expectedZoom) > 0.2)
	{
		_currentZoom += 0.1;
		view.zoom(1.025);
	}

	if (_currentZoom > _expectedZoom && abs(_currentZoom-_expectedZoom) > 0.2)
	{
		_currentZoom -= 0.1;
		view.zoom(0.975);
	}

	window->setView(view);
}

void CellSimApp::updateViewCenter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		if (CellSimMouse::wasRigthReleased())
		{
			auto prev = view.getCenter();
			view.setCenter(CellSimMouse::getPosition());

			auto envs = Environment::getInstance().getSize();
			if (!sf::FloatRect(0, 0, envs.x, envs.y).contains(view.getCenter()))
				view.setCenter(prev);
		}
	}
	else if (CellSimMouse::isRightPressed())
	{
		auto mv = CellSimMouse::getPositionShift()*(-0.5f);
		auto prev = view.getCenter();
		view.move(static_cast<sf::Vector2f>(mv));

		auto envs = Environment::getInstance().getSize();
		if (!sf::FloatRect(0, 0, envs.x, envs.y).contains(view.getCenter()))
			view.setCenter(prev);
	}
}


