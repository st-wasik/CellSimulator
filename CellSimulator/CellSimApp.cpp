#include "CellSimApp.h"
#include "CellSimMouse.h"
#include "Environment.h"
#include "CellSelectionTool.h"
#include "MainApp.h"
#include "Logger.h"
#include "FilesManager.h"
#include "GUIManager.h"
#include "TextureProvider.h"
#include "MessagesManager.h"
#include "CellInsertionTool.h"
#include "CellFactory.h"
#include <iostream>
#include <atomic>

CellSimApp& CellSimApp::getInstance()
{
	static CellSimApp instance;
	return instance;
}

CellSimApp::CellSimApp()
{
	deltaTime = 0;
	fps = 0;
}

CellSimApp::~CellSimApp()
{
}

void CellSimApp::run()
{
	MessagesManager::getInstance().configure();
	Environment::getInstance().configure({2000,1000}, true);
	GUIManager::getInstance().configure(window);

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
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				MainApp::close();

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
				MessagesManager::getInstance().append("Simulation saved as quick_save.cell.");
				if (wasSimActive)
					Environment::getInstance().startSimualtion();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				bool wasSimActive = Environment::getInstance().getIsSimulationActive();
				Environment::getInstance().pauseSimulation();
				MessagesManager::getInstance().append("Loading simulation from file...");
				std::string saveString;
				try
				{
					saveString = FilesManager::getInstance().readFile("quick_save");
				}
				catch (std::exception e)
				{
					Logger::log(e.what());
				}

				try
				{
					Environment::getInstance().configure(saveString);
				}
				catch (std::exception e)
				{
					Logger::log(e.what());
				}

				MessagesManager::getInstance().append("Simulation loaded from quick_save.cell.");
				if (wasSimActive)
					Environment::getInstance().startSimualtion();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tilde)
				CellInsertionTool::getInstance().setIsActive(!CellInsertionTool::getInstance().getIsActive());

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
				CellInsertionTool::getInstance().setCellBlueprint(CellFactory::getCell(Cell::Type::Aggressive));
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
				CellInsertionTool::getInstance().setCellBlueprint(CellFactory::getCell(Cell::Type::Passive));
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
				CellInsertionTool::getInstance().setCellBlueprint(CellFactory::getCell(Cell::Type::Random));
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
				CellInsertionTool::getInstance().setCellBlueprint(CellFactory::getCell(Cell::Type::GreenLettuce));


			GUIManager::getInstance().handleEvent(event);
		}
		//UPDATE --->
		updateViewCenter();
		updateViewZoom();

		GUIManager::getInstance().update();
		Environment::getInstance().update();

		//DRAW --->
		window->clear();

		Environment::getInstance().draw(*window);
		GUIManager::getInstance().draw();

		window->display();

		//OTHER --->
		deltaTime = 0.0001 * deltaTimeClock.getElapsedTime().asMicroseconds();
		fps = 1 / (deltaTime * 100);
	}
}

void CellSimApp::configure()
{
	window = std::make_shared<sf::RenderWindow>();
	//windowVideoMode = sf::VideoMode(1378, 768);
	windowVideoMode = sf::VideoMode::getDesktopMode();
	windowTitle = "Cell Simulator";

	Logger::log(windowTitle + " - build " + __DATE__ + " " + __TIME__);

	// first getInstance call loads all textures
	TextureProvider::getInstance();

	window->create(windowVideoMode, windowTitle, sf::Style::Fullscreen);
	window->setFramerateLimit(60);
	window->setPosition({ 0,0 });
	window->setVerticalSyncEnabled(true);

	//sf::Image icon;
	//icon.loadFromFile("./textures/icon.png");
	//window->setIcon(200, 200, icon.getPixelsPtr());

	view.setSize(sf::Vector2f(windowVideoMode.width, windowVideoMode.height));
	view.setCenter(sf::Vector2f(windowVideoMode.width / 2, windowVideoMode.height / 2));
	window->setView(view);
	window->setActive();

	if (!font.loadFromFile("./fonts/Amble/Amble-Bold.ttf"))
	{
		Logger::log("Cannot load font.");
		throw std::exception("Cannot load font.");
	}
	else
	{
		Logger::log("Font loaded.");
	}
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

const sf::Font & CellSimApp::getFont()
{
	return font;
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


