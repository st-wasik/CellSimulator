#include "Environment.h"
#include "Logger.h"
#include "CellSimMouse.h"
#include "CellSelectionController.h"
#include <math.h>
#include <random>
#include <algorithm>

double getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	double x = abs(a.x - b.x);
	double y = abs(a.y - b.y);
	return sqrt(x * x + y * y);
}

std::vector<Cell> Environment::cells;

std::vector<int/*Substance*/> Environment::substances;

sf::RectangleShape Environment::environmentBackground;

sf::RectangleShape Environment::temperatureBackground;

double Environment::_temperature;

double Environment::_radiation;

sf::Texture Environment::backgroundImage;

void Environment::clear()
{
	cells.clear();
	substances.clear();
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
	std::uniform_int_distribution<std::mt19937::result_type> distW(50, 800 - 40);
	std::uniform_int_distribution<std::mt19937::result_type> distH(50, 600 - 40);

	for (int i = 0; i < 50; i++) {
		cells.insert(cells.end(), Cell(20, sf::Vector2f(distW(rng), distH(rng))));
	}
}

void Environment::update()
{
	if (_temperature < -30) 
		temperatureBackground.setFillColor(sf::Color(0, 0, -_temperature + 155, (_temperature < -30) ? (-_temperature - 30) : 0));
	else if (_temperature > 30) 
		temperatureBackground.setFillColor(sf::Color(_temperature + 155, 0, 0, (_temperature > 30) ? (_temperature - 30): 0));

	sf::Vector2f mouse = CellSimMouse::getPosition();
	//cell selection
	if (CellSimMouse::wasLeftPressed())
	{
		CellSelectionController::clearSelectedCell();
		auto selectedCell = std::find_if(cells.begin(), cells.end(), [&](Cell& c) {return getDistance(c.getPosition(), mouse) < c.getSize(); });
		if (selectedCell != cells.end())
		{
			CellSelectionController::setSelectedCell(selectedCell);
		}
	}

	for (auto& cell : cells)
	{
		cell.update();
	}

	CellSelectionController::update();
	////cell moving
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
	for (auto & cell : cells) {
		window.draw(cell);
	}
	CellSelectionController::draw(window);
}

double Environment::getTemperature()
{
	return _temperature;
}

void Environment::setTemperature(const double & t)
{
	_temperature = t;
}

double Environment::getRadiation()
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

std::vector<Cell>::iterator Environment::getCellAtPosition(const sf::Vector2f & p)
{
	return std::find_if(cells.begin(), cells.end(), [&](Cell& c) {
		return getDistance(c.getPosition(), p) < c.getSize();
	});;
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
