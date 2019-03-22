#include "Environment.h"
#include "Logger.h"
#include "CellSimMouse.h"
#include "CellSelectionController.h"
#include <math.h>
#include <random>
#include <algorithm>
#include <atomic>
#include "TextureProvider.h"
double getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	auto v = a - b;
	return sqrt(v.x*v.x + v.y*v.y);
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
	backgroundDefaultColor = sf::Color{ 170, 135, 200 };

	auto& eb = environmentBackground;
	eb.setSize(sf::Vector2f{ 2000,1000 });
	eb.setFillColor(backgroundDefaultColor);
	eb.setOutlineColor(sf::Color::Red);
	eb.setOutlineThickness(5);
	eb.setPosition(sf::Vector2f{ 0,0 });
	eb.setTextureRect(sf::IntRect(0, 0, eb.getSize().x / 10, eb.getSize().y / 10));
	eb.setTexture(TextureProvider::getInstance().getTexture("background").get());

	temperatureBackground.setSize(eb.getSize());
	temperatureBackground.setPosition(eb.getPosition());
	temperatureBackground.setFillColor(sf::Color::Transparent);

	for (int i = 0; i < 50; i++) {
		cells.push_back(std::make_shared<Cell>(
			20,
			sf::Vector2f(randomInt(40, static_cast<int>(Environment::getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getSize().y - 40))),
			sf::Color(randomInt(0, 255), randomInt(0, 64), randomInt(0, 255))));
	}

	for (int i = 0; i < 100; i++) {
		food.push_back(std::make_shared<Food>(
			randomInt(3, 12),
			sf::Vector2f(randomInt(40, static_cast<int>(Environment::getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getSize().y - 40))),
			sf::Color(0, randomInt(128, 255), randomInt(0, 64))));
	}

	TextureProvider::getInstance().getTexture("whiteNoise")->setSmooth(true);
}

void Environment::updateBackground()
{
	static double threshold = 30;
	int newR, newG, newB;

	auto newColor = backgroundDefaultColor;

	//temperature
	auto& envTemp = _temperature;
	auto& envRad = _radiation;
	if (envTemp > threshold)
	{
		newR = 2 * abs(envTemp - threshold) + backgroundDefaultColor.r;
		if (newR > 255) newR = 255;
		newColor.r = newR;
	}
	else if (envTemp < -threshold)
	{
		newB = 2 * abs(envTemp + threshold) + backgroundDefaultColor.b;
		if (newB > 255) newB = 255;
		newColor.b = newB;
	}

	//radiation
	if (envRad > threshold)
	{
		newG = 3 * abs(envRad - threshold) + backgroundDefaultColor.g;
		if (newG > 255) newG = 255;
		newColor.g = newG;
	}

	environmentBackground.setFillColor(newColor);
}

void Environment::update()
{
	sf::Vector2f mouse = CellSimMouse::getPosition();

	_aliveCellsCount = cells.size();
	_foodCount = food.size();

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

	CellSelectionController::update();
	updateBackground();

	//remove food marked to delete
	auto newFoodEnd = std::remove_if(food.begin(), food.end(), [](auto f) {return f->toDelete; });
	food.erase(newFoodEnd, food.end());

	//remove cells marked to delete
	auto newCellsEnd = std::remove_if(cells.begin(), cells.end(), [](auto c) {return c->toDelete; });
	cells.erase(newCellsEnd, cells.end());




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

}

void Environment::draw(sf::RenderWindow & window)
{
	window.draw(environmentBackground);
	window.draw(temperatureBackground);
	for (auto & f : food) {
		window.draw(*f);
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

int Environment::getAliveCellsCount()
{
	return _aliveCellsCount;
}

int Environment::getFoodCount()
{
	return _foodCount;
}

std::shared_ptr<Cell> Environment::getCellAtPosition(const sf::Vector2f & p)
{
	auto result = std::find_if(cells.begin(), cells.end(), [&](std::shared_ptr<Cell>& c) {
		return getDistance(c->getPosition(), p) < c->getSize(); });

	if (result != cells.end()) return *result;
	return nullptr;
}

std::vector<std::shared_ptr<Food>>& Environment::getFoodsVector()
{
	return food;
}

std::vector<std::shared_ptr<Cell>>& Environment::getCellsVector()
{
	return cells;
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
