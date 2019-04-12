#include "Environment.h"
#include "Logger.h"
#include "CellSimMouse.h"
#include "CellSelectionTool.h"
#include <math.h>
#include <random>
#include <algorithm>
#include <atomic>
#include "TextureProvider.h"
#include "CellMovementTool.h"
#include "FoodController.h"
#include "AutoFeederTool.h"
#include "Distance.h"
#include "CellFactory.h"

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
	_clearEnvironment = true;
}

void Environment::sterilizeEnvironment()
{
	for (auto& o : cells) o->markToDelete();
	for (auto& o : deadCells) o->markToDelete();
	for (auto& o : food) o->markToDelete();
	cells.clear();
	deadCells.clear();
	food.clear();

	for (auto& c : cellCollisionSectors)
	{
		for (auto& cc : c)
			cc.clear();
	}
	for (auto& f : foodCollisionSectors)
	{
		for (auto& ff : f)
			ff.clear();
	}
}

void Environment::configure()
{
	backgroundDefaultColor = sf::Color{ 170, 135, 200 };

	auto& eb = environmentBackground;
	eb.setSize(sf::Vector2f{ 5000,2500 });
	eb.setFillColor(backgroundDefaultColor);
	eb.setOutlineColor(sf::Color::Red);
	eb.setOutlineThickness(5);
	eb.setPosition(sf::Vector2f{ 0,0 });
	eb.setTextureRect(sf::IntRect(0, 0, eb.getSize().x / 10, eb.getSize().y / 10));
	TextureProvider::getInstance().getTexture("background")->setSmooth(true);
	eb.setTexture(TextureProvider::getInstance().getTexture("background").get());

	TextureProvider::getInstance().getTexture("whiteNoise")->setSmooth(true);


	int sectorsX = getSize().x / sectorSize + 1;
	int sectorsY = getSize().y / sectorSize + 1;

	cellCollisionSectors.resize(sectorsX);
	for (int i = 0; i < sectorsX; ++i)
	{
		cellCollisionSectors[i].resize(sectorsY);
	}

	foodCollisionSectors.resize(sectorsX);
	for (int i = 0; i < sectorsX; ++i)
	{
		foodCollisionSectors[i].resize(sectorsY);
	}


	for (int i = 0; i < 2; i++) {
		auto cell = CellFactory::getCell(Cell::Type::Aggressive);
		cell->setPosition(sf::Vector2f(randomInt(40, static_cast<int>(Environment::getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getSize().y - 40))));
		insertNewCell(cell);
	}

	for (int i = 0; i < 20; i++) {
		auto cell = CellFactory::getCell(Cell::Type::Passive);
		cell->setPosition(sf::Vector2f(randomInt(40, static_cast<int>(Environment::getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getSize().y - 40))));
		insertNewCell(cell);
	}

	for (int i = 0; i < 10; i++) {
		auto cell = CellFactory::getCell(Cell::Type::Random);
		cell->setPosition(sf::Vector2f(randomInt(40, static_cast<int>(Environment::getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getSize().y - 40))));
		insertNewCell(cell);
	}

	for (int i = 0; i < 3; i++) {
		auto cell = CellFactory::getCell(Cell::Type::GreenLettuce);
		cell->setPosition(sf::Vector2f(randomInt(40, static_cast<int>(Environment::getSize().x - 40)), randomInt(40, static_cast<int>(Environment::getSize().y - 40))));
		insertNewCell(cell);
	}

	FoodController::generateFood(sf::Vector2f(3, 12), 100);
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

	updateBackground();

	if (_clearEnvironment)
	{
		_clearEnvironment = false;
		sterilizeEnvironment();
	}

	CellSelectionTool::getInstance().update();
	CellMovementTool::getInstance().update();
	AutoFeederTool::getInstance().update();

	for (auto& newCell : newCells)
	{
		cells.push_back(newCell);
	}
	newCells.clear();

	for (auto& f : newFood)
	{
		food.push_back(f);
	}
	newFood.clear();

	// call role-functions for all cells
	if (_simulationActive)
	{
		for (auto& cell : cells)
		{
			cell->update();

			if (cell->isDead())
				deadCells.push_back(cell);
		}

		for (auto& cell : deadCells)
		{
			cell->update();
		}
	}


	CellSelectionTool::getInstance().updateSelectionMarker();

	//remove food marked to delete in role-functions
	auto newFoodEnd = std::remove_if(food.begin(), food.end(), [](auto f) {return f->isMarkedToDelete(); });
	food.erase(newFoodEnd, food.end());

	//remove food from collision sectors
	for (auto& f : foodCollisionSectors)
		for (auto& ff : f)
			ff.erase(std::remove_if(ff.begin(), ff.end(), [](std::shared_ptr<BaseObj> e) {return e->isMarkedToDelete(); }), ff.end());

	//remove cells marked as dead
	auto newCellsEnd = std::remove_if(cells.begin(), cells.end(), [](auto c) {return c->isDead(); });
	cells.erase(newCellsEnd, cells.end());

	//remove cells marked as dead from collision sectors
	for (auto& c : cellCollisionSectors)
		for (auto& cc : c)
			cc.erase(std::remove_if(cc.begin(), cc.end(), [](std::shared_ptr<BaseObj> e) {return e->isMarkedToDelete(); }), cc.end());

	//remove dead cells marked to delete
	auto newDeadCellsEnd = std::remove_if(deadCells.begin(), deadCells.end(), [](auto c) {return c->isMarkedToDelete(); });
	deadCells.erase(newDeadCellsEnd, deadCells.end());
}

void Environment::updatePausedSim()
{
	sf::Vector2f mouse = CellSimMouse::getPosition();

	_aliveCellsCount = cells.size();
	_foodCount = food.size();

	updateBackground();

	CellSelectionTool::getInstance().update();
	CellMovementTool::getInstance().update();
	AutoFeederTool::getInstance().update();
}

void Environment::draw(sf::RenderWindow & window)
{
	window.draw(environmentBackground);
	for (auto & f : food) {
		window.draw(*f);
	}
	for (auto & cell : deadCells) {
		window.draw(*cell);
	}
	for (auto & cell : cells) {
		window.draw(*cell);
	}
	CellSelectionTool::getInstance().draw(window);
	CellMovementTool::getInstance().draw(window);
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

const std::list<std::shared_ptr<Food>>& Environment::getFoodsVector()
{
	return food;
}

std::vector<std::shared_ptr<Cell>>& Environment::getCellsVector()
{
	return cells;
}

std::vector<std::shared_ptr<Cell>>& Environment::getNewCellsVector()
{
	return newCells;
}

std::list<std::shared_ptr<Food>>& Environment::getNewFoodsVector()
{
	return newFood;
}

baseObjMatrix& Environment::getCellCollisionSectors()
{
	return cellCollisionSectors;
}

baseObjMatrix& Environment::getFoodCollisionSectors()
{
	return foodCollisionSectors;
}

void Environment::insertNewCell(std::shared_ptr<Cell> c)
{
	newCells.push_back(c);

	auto coords = getCollisionSectorCoords(c);
	cellCollisionSectors[coords.x][coords.y].push_back(c);
}

void Environment::insertNewFood(std::shared_ptr<Food> f)
{
	newFood.push_back(f);

	auto coords = getCollisionSectorCoords(f);
	foodCollisionSectors[coords.x][coords.y].push_back(f);
}

Environment::Environment()
{
	_clearEnvironment = false;
	_simulationActive = true;
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

sf::Vector2i Environment::getCollisionSectorCoords(std::shared_ptr<BaseObj> o)
{
	return sf::Vector2i(o->getPosition().x / sectorSize, o->getPosition().y / sectorSize);
}

void Environment::pauseSimulation()
{
	_simulationActive = false;
	AutoFeederTool::getInstance().setIsActive(false);
}

void Environment::startSimualtion()
{
	_simulationActive = true;
	AutoFeederTool::getInstance().setIsActive(true);
}

std::atomic_bool & Environment::getSimulationState()
{
	return _simulationActive;
}
