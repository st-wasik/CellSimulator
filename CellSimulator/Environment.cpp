#include "Environment.h"
#include "CellSimApp.h"
#include "Logger.h"
#include "CellSimMouse.h"
#include "CellSelectionTool.h"
#include "CellInsertionTool.h"
#include "FoodBrush.h"
#include <math.h>
#include <random>
#include <algorithm>
#include <atomic>
#include "TextureProvider.h"
#include "CellMovementTool.h"
#include "FoodManager.h"
#include "AutoFeederTool.h"
#include "Distance.h"
#include "RegexPattern.h"
#include "CellFactory.h"
#include "MessagesManager.h"
#include <sstream>
#include <regex>

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
	MessagesManager::getInstance().append("Environment cleared.");
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

void Environment::configure(sf::Vector2f envSize, bool fill)
{
	sterilizeEnvironment();

	//backgroundDefaultColor = sf::Color{ 170, 135, 200 };
	//backgroundDefaultColor = sf::Color{ 50, 60, 40 };
	backgroundDefaultColor = sf::Color{ 60, 60, 30 };

	auto& eb = environmentBackground;
	eb.setSize(envSize);
	eb.setFillColor(backgroundDefaultColor);
	eb.setOutlineColor(sf::Color::Red);
	eb.setOutlineThickness(5);
	eb.setPosition(sf::Vector2f{ 0,0 });
	eb.setTextureRect(sf::IntRect(0, 0, eb.getSize().x / 25, eb.getSize().y / 25));
	TextureProvider::getInstance().getTexture("background2")->setSmooth(true);
	eb.setTexture(TextureProvider::getInstance().getTexture("background2").get());

	CellSimApp::getInstance().getView().setCenter(eb.getSize()/2.0f);

	//TextureProvider::getInstance().getTexture("whiteNoise")->setSmooth(true);


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

	if (fill)
	{
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

		FoodManager::generateFood(sf::Vector2f(3, 12), 100);
	}
}

void Environment::configure(std::string formattedEnvString)
{
	static std::string doubleRegex(RegexPattern::Double);
	static std::string vectorRegex(RegexPattern::Vector);
	static std::string word(RegexPattern::Word);

	static std::regex envRegex("^ENVIRONMENT->( " + word + ":((" + doubleRegex + ")|(" + vectorRegex + ")))* ");
	//std::regex envRegex("^ENVIRONMENT->( [a-zA-Z_]+:(([0-9]+\\.?[0-9]*)|(\\{[0-9]+\\.?[0-9]*(, [0-9]+\\.?[0-9]*)*\\})))*$");
	static std::regex cellHeader("^CELL->");
	static std::regex foodHeader("^FOOD->");
	static std::regex empty("^$");

	std::vector<std::string> lines;
	std::istringstream input(formattedEnvString);

	while (true)
	{
		std::string tempString;
		std::getline(input, tempString, '\n');
		if (input.eof()) break;
		lines.push_back(tempString);
	}

	if (lines.size() == 0)
	{
		Logger::log("Save string is empty!");
		return;
	}
	if (!std::regex_match(lines[0].begin(), lines[0].end(), envRegex))
	{
		Logger::log("Environment string wrong format!");
		return;
	}

	std::regex envSettingsRegex(" " + word + ":(" + doubleRegex + "|" + vectorRegex + ")");
	auto envSettingsBegin = std::sregex_iterator(lines[0].begin(), lines[0].end(), envSettingsRegex);
	auto envSettingsEnd = std::sregex_iterator();

	for (auto i = envSettingsBegin; i != envSettingsEnd; ++i)
	{
		std::string settingStr = i->str();
		std::regex type(word);
		std::regex value(doubleRegex);
		std::regex vectorValue(vectorRegex);

		auto type_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), type);
		auto value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), value);
		auto vector_value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), vectorValue);

		if (type_i != std::sregex_iterator() && vector_value_i != std::sregex_iterator())
		{
			std::regex value(RegexPattern::Double);
			auto vector_value_s = vector_value_i->str();
			auto valuesBegin = std::sregex_iterator(vector_value_s.begin(), vector_value_s.end(), value);
			std::vector<std::string> values_vect;
			for (auto it = value_i; it != std::sregex_iterator(); it++)
			{
				values_vect.push_back(it->str());
			}
			modifyValueFromVector(type_i->str(), values_vect);
		}
		else if (type_i != std::sregex_iterator() && value_i != std::sregex_iterator())
			modifyValueFromString(type_i->str(), value_i->str());
	}

	auto size = lines.size();
	for (int i = 1; i < size; ++i)
	{
		if (i % 512 == 0) Logger::log("Load from file: " + std::to_string(i) + "/" + std::to_string(size));

		if (std::regex_match(lines[i].begin(), lines[i].end(), empty))
			continue;
		else if (std::regex_search(lines[i].begin(), lines[i].end(), cellHeader))
		{
			insertNewCell(Cell::create(lines[i]));
		}
		else if (std::regex_search(lines[i].begin(), lines[i].end(), foodHeader))
		{
			insertNewFood(Food::create(lines[i]));
		}
		else Logger::log("Not recognized data format in environment save string.");
	}

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

	CellMovementTool::getInstance().update();
	CellSelectionTool::getInstance().update();
	AutoFeederTool::getInstance().update();
	CellInsertionTool::getInstance().update();
	FoodBrush::getInstance().update();

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
	CellInsertionTool::getInstance().draw(window);
	FoodBrush::getInstance().draw(window);
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

const std::vector<std::shared_ptr<Food>>& Environment::getFoodsVector()
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

const std::vector<std::shared_ptr<Food>>& Environment::getNewFoodsVector()
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

std::string Environment::getSaveString()
{
	std::ostringstream result;

	result << "ENVIRONMENT-> " <<
		VarAbbrv::envSize << ":{" << this->environmentBackground.getSize().x << ", " << this->environmentBackground.getSize().y << "} " <<
		VarAbbrv::radiation << ":" << this->getRadiation() << " " <<
		VarAbbrv::temperature << ":" << this->getTemperature() << " " <<
		VarAbbrv::isSimualtionActive << ":" << this->getIsSimulationActive() << " " << std::endl << std::endl;

	for (auto& o : newCells) result << o->getSaveString() << std::endl;
	for (auto& o : cells) result << o->getSaveString() << std::endl;
	for (auto& o : deadCells) result << o->getSaveString() << std::endl;
	result << std::endl;
	for (auto& o : newFood) result << o->getSaveString() << std::endl;
	for (auto& o : food) result << o->getSaveString() << std::endl;

	return result.str();
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

void Environment::modifyValueFromString(std::string valueName, std::string value)
{
	Logger::log("Setting '" + valueName + "' to " + value);
	auto& v = valueName;

	if (v == VarAbbrv::isSimualtionActive)		this->_simulationActive = (std::stod(value));
	else if (v == VarAbbrv::radiation)			this->_radiation = (std::stod(value));
	else if (v == VarAbbrv::temperature)		this->_temperature = (std::stod(value));
	else Logger::log(std::string("Unknown environment var name '" + v + "' with value '" + value + "'!"));
}

void Environment::modifyValueFromVector(std::string valueName, const std::vector<std::string>& values)
{
	Logger::log("Setting '" + valueName + "'.");
	auto& v = valueName;
	if (v == VarAbbrv::envSize)
	{
		if (values.size() != 2)
		{
			Logger::log("Wrong values count for " + std::string(VarAbbrv::envSize) + ".");
			return;
		}
		configure(sf::Vector2f(std::stod(values[0]), std::stod(values[1])));
	}
}

sf::Vector2i Environment::getCollisionSectorCoords(std::shared_ptr<BaseObj> o)
{
	return sf::Vector2i(o->getPosition().x / sectorSize, o->getPosition().y / sectorSize);
}

void Environment::pauseSimulation()
{
	if (_simulationActive)
		MessagesManager::getInstance().append("Simulation paused.");
	_simulationActive = false;
	AutoFeederTool::getInstance().setIsActive(false);
}

void Environment::startSimualtion()
{
	if (!_simulationActive)
		MessagesManager::getInstance().append("Simulation resumed.");
	_simulationActive = true;
	AutoFeederTool::getInstance().setIsActive(true);
}

std::atomic_bool & Environment::getIsSimulationActive()
{
	return _simulationActive;
}
