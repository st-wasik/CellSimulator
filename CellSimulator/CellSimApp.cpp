#include "CellSimApp.h"
#include "CellSimMouse.h"
#include "Environment.h"
#include "CellSelectionTool.h"
#include "MainApp.h"
#include "Logger.h"
#include "FilesManager.h"
#include <iostream>
#include <atomic>

CellSimApp& CellSimApp::getInstance()
{
	static CellSimApp instance;
	return instance;
}

CellSimApp::~CellSimApp()
{
}

void CellSimApp::run()
{
	Environment::getInstance().configure();

	view.setCenter(sf::Vector2f(Environment::getInstance().getSize().x / 2, Environment::getInstance().getSize().y / 2));

	sf::Event event;
	sf::Clock deltaTimeClock;

	while (window->isOpen())
	{
		if (!MainApp::appRun)
		{
			window->close();
			break;
		}

		deltaTimeClock.restart();
		CellSimMouse::update();

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainApp::close();

			if (event.type == sf::Event::MouseWheelScrolled)
				CellSimMouse::setWheelDelta(event.mouseWheelScroll.delta);

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Subtract)
				if (_expectedZoom < _minZoom)
					_expectedZoom += 2;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Add)
				if (_expectedZoom > _maxZoom)
					_expectedZoom -= 2;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				CellSelectionTool::getInstance().setFollowSelectedCell(true);

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
				Environment::getInstance().clear();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
				if (Environment::getInstance().getIsSimulationActive())
					Environment::getInstance().pauseSimulation();
				else
					Environment::getInstance().startSimualtion();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
			{
				bool wasSimActive = Environment::getInstance().getIsSimulationActive();
				Environment::getInstance().pauseSimulation();

				try
				{
					FilesManager::getInstance().writeFile("quick_save", Environment::getInstance().getSaveString());
				}
				catch (std::exception e)
				{
					Logger::log(e.what());
				}

				if (wasSimActive)
					Environment::getInstance().startSimualtion();
			}

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
	window->setPosition({ 300,20 });
	//window->setVerticalSyncEnabled(true);

	view.setSize(sf::Vector2f(windowVideoMode.width, windowVideoMode.height));
	view.setCenter(sf::Vector2f(windowVideoMode.width / 2, windowVideoMode.height / 2));
	window->setView(view);
	window->setActive();
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

CellSimApp::CellSimApp()
{
}

void CellSimApp::updateViewZoom()
{
	//std::cout << "Min: "<<_minZoom << "  Max: " << _maxZoom << "  Exp: " << _expectedZoom << "  Curr: " << _currentZoom << std::endl;

	if (CellSimMouse::getWheelDelta() < 0)
	{
		if (_expectedZoom < _minZoom)
			_expectedZoom += 2;
	}
	else if (CellSimMouse::getWheelDelta() > 0)
	{
		if (_expectedZoom > _maxZoom)
			_expectedZoom -= 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) && window->hasFocus()) _expectedZoom = 0;

	if (_currentZoom < _expectedZoom && abs(_currentZoom - _expectedZoom) > 0.2)
	{
		_currentZoom += 0.1;
		view.zoom(1.025);
	}

	if (_currentZoom > _expectedZoom && abs(_currentZoom - _expectedZoom) > 0.2)
	{
		_currentZoom -= 0.1;
		view.zoom(0.975);
	}

	window->setView(view);
}

void CellSimApp::updateViewCenter()
{
	if (CellSelectionTool::getInstance().getFollowSelectedCell())
	{
		auto cell = CellSelectionTool::getInstance().getSelectedCell();
		if (cell != nullptr)
		{
			view.setCenter(cell->getPosition());
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		if (CellSimMouse::wasRigthReleased())
		{
			CellSelectionTool::getInstance().setFollowSelectedCell(false);

			auto prev = view.getCenter();
			view.setCenter(CellSimMouse::getPosition());

			auto envs = Environment::getInstance().getSize();
			if (!sf::FloatRect(0, 0, envs.x, envs.y).contains(view.getCenter()))
				view.setCenter(prev);
		}
	}
	else if (CellSimMouse::isRightPressed())
	{
		CellSelectionTool::getInstance().setFollowSelectedCell(false);

		auto mv = CellSimMouse::getPositionShift()*(-0.5f);
		auto prev = view.getCenter();
		view.move(static_cast<sf::Vector2f>(mv));

		auto envs = Environment::getInstance().getSize();
		if (!sf::FloatRect(0, 0, envs.x, envs.y).contains(view.getCenter()))
			view.setCenter(prev);
	}
}


