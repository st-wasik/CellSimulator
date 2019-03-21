#include "Environment.h"
#include "Logger.h"
#include "CellSimMouse.h"
#include "CellSelectionController.h"
#include <math.h>
#include <random>
#include <algorithm>
#include <atomic>

double getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	double x = abs(a.x - b.x);
	double y = abs(a.y - b.y);
	return sqrt(x * x + y * y);
}

Environment::~Environment()
{
}

Environment& Environment::getInstance()
{
	static Environment instance;
	return instance;
}

void Environment::clear()
{
	cells.clear();
	substances.clear();
	food.clear();
}

void Environment::configure()
{
	backgroundImage.loadFromFile("./Images/background.png");
	backgroundImage.setRepeated(true);

	auto& eb = environmentBackground;
	eb.setSize(sf::Vector2f{ 2000,1000 });
	eb.setFillColor(sf::Color{ 170, 135, 200 });
	eb.setOutlineColor(sf::Color::Red);
	eb.setOutlineThickness(5);
	eb.setPosition(sf::Vector2f{ 0,0 });
	eb.setTextureRect(sf::IntRect(0, 0, eb.getSize().x, eb.getSize().y));
	eb.setTexture(&backgroundImage);

	temperatureBackground.setSize(eb.getSize());
	temperatureBackground.setPosition(eb.getPosition());
	temperatureBackground.setFillColor(sf::Color::Transparent);

	//To be positioned elsewhere in future
	std::random_device dev;
	std::mt19937 rng(dev());
	
	std::uniform_int_distribution<std::mt19937::result_type> distW(40, static_cast<int>(Environment::getSize().x - 40));
	std::uniform_int_distribution<std::mt19937::result_type> distH(40, static_cast<int>(Environment::getSize().y - 40));

	for (int i = 0; i < 50; i++) {
		cells.push_back(std::make_shared<Cell>(20, sf::Vector2f(distW(rng), distH(rng))));
	}

	for (int i = 0; i < 100; i++) {
		food.push_back(std::make_shared<Food>(randomInt(3, 12), sf::Vector2f(distW(rng), distH(rng)), sf::Color(0, randomInt(64, 128), randomInt(192, 255))));
	}
}

void Environment::update()
{
	if (_temperature < -30)
		temperatureBackground.setFillColor(sf::Color(0, 0, -_temperature + 155, (_temperature < -30) ? (-_temperature - 30) : 0));
	else if (_temperature > 30)
		temperatureBackground.setFillColor(sf::Color(_temperature + 155, 0, 0, (_temperature > 30) ? (_temperature - 30) : 0));

	sf::Vector2f mouse = CellSimMouse::getPosition();

	//cell selection
	if (CellSimMouse::wasLeftPressed())
	{
		CellSelectionController::clearSelectedCell();
		auto selectedCell = std::find_if(cells.begin(), cells.end(), [&](std::shared_ptr<Cell> c) {return getDistance(c->getPosition(), mouse) < c->getSize(); });
		if (selectedCell != cells.end())
		{
			CellSelectionController::setSelectedCell(*selectedCell);
		}
	}

	for (auto& cell : cells)
	{
		cell->update();
	}

	/*for (auto& food : food)
	{
		food->update();
	}*/

	CellSelectionController::update();


	////cell moving by user
	//if (CellSimMouse::isLeftPressed() && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	//{
	//	if (cellSelectionValid)
	//	{
	//		selectedCell->freeze();
	//		auto cellPos = selectedCell->getPosition();
	//		selectedCell->setPosition(CellSimMouse::getPosition());

	//		if (!isCellInEnvironmentBounds(*selectedCell))
	//		{
	//			selectedCell->setPosition(cellPos);
	//		}
	//	}
	//}
	//else
	//{
	//	if (cellSelectionValid)
	//	{
	//		selectedCell->unfreeze();
	//	}
	//}

	//if (cellSelectionValid)
	//	Logger::log(selectedCell->toString());

	for (auto & subst : substances)
	{
		//subst.update();
	}
}

void Environment::draw(sf::RenderWindow & window)
{
	window.draw(environmentBackground);
	window.draw(temperatureBackground);
	for (auto & food : food) {
		window.draw(*food);
	}
	for (auto & cell : cells) {
		window.draw(*cell);
	}
	CellSelectionController::draw(window);
}

std::atomic<double>& Environment::getTemperature()
{
	return _temperature;
}

void Environment::setTemperature(const double& t)
{
	_temperature = t;
}

std::atomic<double>& Environment::getRadiation()
{
	return _radiation;
}

void Environment::setRadiation(const double & r)
{
	_radiation = r;
}

sf::Vector2f Environment::getSize()
{
	return environmentBackground.getSize();
}

unsigned int Environment::getAliveCellsCount()
{
	return cells.size();
}

std::shared_ptr<Cell> Environment::getCellAtPosition(const sf::Vector2f & p)
{
	auto result = std::find_if(cells.begin(), cells.end(), [&](std::shared_ptr<Cell>& c) {
		return getDistance(c->getPosition(), p) < c->getSize();});

	if (result != cells.end()) return *result;
	return nullptr;
}

Environment::Environment()
{
	configure();
}

bool Environment::isCellInEnvironmentBounds(Cell & c)
{
	const auto& envSize = getSize();
	const auto& cellPos = c.getPosition();

	//check left bound
	if (c.getPosition().x - c.getSize() <= 0)
	{
		return false;
	}
	//check right bound
	else if (c.getPosition().x + c.getSize() >= envSize.x)
	{
		return false;
	}
	//check top bound
	else if (c.getPosition().y - c.getSize() <= 0)
	{
		return false;
	}
	//check bottom bound
	else if (c.getPosition().y + c.getSize() >= envSize.y)
	{
		return false;
	}
	return true;
}
