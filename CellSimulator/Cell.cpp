#include "Cell.h"
#include "Food.h"
#include "CellRoles.h"
#include "CellSimApp.h"
#include "Environment.h"
#include "BaseObj.h"
#include "TextureProvider.h"
#include <sstream>
#include <regex>

Cell::Cell(float size, sf::Vector2f position, sf::Color color) : BaseObj(size, position, color)
{
	this->age = 0;

	this->foodLevel = 50;

	this->currentSpeed = randomReal(0.1, genes.maxSpeed.get());

	this->horniness.randomize();

	shape.setOutlineColor(sf::Color::Yellow);


	int textureSize = getSize() / 2;
	shape.setTextureRect({ 0,0,textureSize, textureSize });
	shape.setTexture(TextureProvider::getInstance().getTexture("whiteNoise").get());

	shape.setOutlineThickness(-5);
	shape.setOutlineColor(sf::Color(128, 64, 0, 75));

	// name of function is its address
	// place here all role-functions that cell should call
	roles.push_back(CellRoles::changeDirection);
	roles.push_back(CellRoles::changeSpeed);
	roles.push_back(CellRoles::eat);
	roles.push_back(CellRoles::updateColor);
	roles.push_back(CellRoles::simulateHunger);
	roles.push_back(CellRoles::divideAndConquer);
	roles.push_back(CellRoles::getingHot);
	//roles.push_back(CellRoles::grow);
	//roles.push_back(CellRoles::fight);
	roles.push_back(CellRoles::makeOlder);
	roles.push_back(CellRoles::mutate);


	// make sure that moveForward is always the last role-function
	// cell should be moved after all updates
	roles.push_back(CellRoles::moveForward);
}

Cell::Cell(Cell a, Cell b) : Cell(20, (a.getPosition() + b.getPosition()) / 2.0f, a.getBaseColor()*b.getBaseColor())
{



	double mutationRatio = Environment::getInstance().getRadiation();
	genes.aggresion = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.aggresion.get(), b.genes.divisionThreshold.get()) : (a.genes.aggresion.get() + b.genes.divisionThreshold.get()) / 2;
	genes.divisionThreshold = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.divisionThreshold.get(), b.genes.divisionThreshold.get()) : (a.genes.divisionThreshold.get() + b.genes.divisionThreshold.get()) / 2;
	genes.foodLimit = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.foodLimit.get(), b.genes.foodLimit.get()) : (a.genes.foodLimit.get() + b.genes.foodLimit.get()) / 2;
	genes.maxAge = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.maxAge.get(), b.genes.maxAge.get()) : (a.genes.maxAge.get() + b.genes.maxAge.get()) / 2;
	genes.maxSize = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.maxSize.get(), b.genes.maxSize.get()) : (a.genes.maxSize.get() + b.genes.maxSize.get()) / 2;
	genes.maxSpeed = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.maxSpeed.get(), b.genes.maxSpeed.get()) : (a.genes.maxSpeed.get() + b.genes.maxSpeed.get()) / 2;
	genes.radarRange = mutationRatio <= randomReal(0, 100) ? MixDouble(a.genes.radarRange.get(), b.genes.radarRange.get()) : (a.genes.radarRange.get() + b.genes.radarRange.get()) / 2;


}

Cell::Cell(std::string formattedCellString) : Cell(0, { 0,0 }, sf::Color::Transparent)
{
	std::string doubleRegex("[0-9]+\\.?[0-9]*");
	std::string vectorRegex("\\{" + doubleRegex + "(, " + doubleRegex + ")*\\}");
	std::regex cellRegex("CELL->( [A-Z]+:(" + doubleRegex + "|" + vectorRegex + "))*");
	if (!std::regex_match(formattedCellString.begin(), formattedCellString.end(), cellRegex))
	{
		throw std::exception("Cell string wrong format!");
	}

	std::regex settingRegex(" [A-Z]+:[0-9]+\\.?[0-9]*");

	auto settingsBegin = std::sregex_iterator(formattedCellString.begin(), formattedCellString.end(), settingRegex);
	auto settingsEnd = std::sregex_iterator();

	for (auto i = settingsBegin; i != settingsEnd; ++i)
	{
		std::string settingStr = i->str();
		std::regex type("[A-Z]+");
		std::regex value(doubleRegex);
		std::regex vectorValue(vectorRegex);

		auto type_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), type);
		auto value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), value);
		auto vector_value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), vectorValue);

		std::string type_s;
		std::string value_s;
		std::string vector_value_s;

		if (type_i != std::sregex_iterator())
		{
			type_s = type_i->str();
		}

		if (value_i != std::sregex_iterator())
		{
			value_s = value_i->str();
		}

		if (vector_value_i != std::sregex_iterator())
		{
			vector_value_s = value_i->str();
		}

		if (!type_s.empty() && !value_s.empty())
			modifyValueFromString(type_s, value_s);
		else if (!type_s.empty() && !vector_value_s.empty())
			modifyValueFromString(type_s, value_s);
	}
}

void Cell::modifyValueFromString(std::string valueName, std::string value)
{
	Logger::log("Setting '" + valueName + "' to " + value);
	auto& v = valueName;

	if (v == VarAbbrv::currentRotation)			this->setRotation(std::stod(value));
	else if (v == VarAbbrv::currentPosition)	this->setPosition(sf::Vector2f(std::stod(value), getPosition().y));
	else if (v == VarAbbrv::color)
	{
		auto c = getBaseColor();
		c.r = std::stod(value);
		this->setBaseColor(c);
	}
	else if (v == VarAbbrv::currentAge)			this->setAge(std::stod(value));
	else if (v == VarAbbrv::currentSpeed)		this->currentSpeed = (std::stod(value));
	else if (v == VarAbbrv::currentSize)		this->setSize((std::stod(value)));
	else if (v == VarAbbrv::isDead)				this->dead = (std::stod(value));
	else if (v == VarAbbrv::currentFoodLevel)	this->foodLevel = (std::stod(value));
	else if (v == VarAbbrv::isFreezed)			this->freezed = (std::stod(value));
	else if (v == VarAbbrv::horniness)			this->horniness = (std::stod(value));
	else if (v == VarAbbrv::aggression)			this->genes.aggresion = (std::stod(value));
	else if (v == VarAbbrv::divisionTh)			this->genes.divisionThreshold = (std::stod(value));
	else if (v == VarAbbrv::foodLimit)			this->genes.foodLimit = (std::stod(value));
	else if (v == VarAbbrv::maxAge)				this->genes.maxAge = (std::stod(value));
	else if (v == VarAbbrv::maxSize)			this->genes.maxSize = (std::stod(value));
	else if (v == VarAbbrv::maxSpeed)			this->genes.maxSpeed = (std::stod(value));
	else if (v == VarAbbrv::radarRange)			this->genes.radarRange = (std::stod(value));
	//else throw std::exception(std::string("Unknown cell var name '" + v + "' with value '" + value + "'!").c_str());
}

Cell::~Cell()
{
}

void Cell::update()
{
	if (!freezed)
		for (auto& fn : roles)
		{
			fn(this);
		}
}

void Cell::freeze()
{
	freezed = true;

	// change A to 255 when unfreezing is not nessesery because cell role updates shape's color 
	auto color = getBaseColor();
	color.a = 128;
	shape.setFillColor(color);
}

void Cell::unfreeze()
{
	freezed = false;
}

void Cell::kill()
{
	if (!dead)
	{
		dead = true;
		roles.clear();
		roles.push_back(CellRoles::beDead);

		auto color = randomInt(0, 32);
		shape.setFillColor(sf::Color(color, color, color, 255));

		auto size = getSize();

		int foods = size / 10;
		auto foodSize = 0.75 * size / foods;

		for (int i = 0; i < foods; ++i)
		{
			float xDeviation = randomInt(-size / 2, size / 2);
			float yDeviation = randomInt(-size / 2, size / 2);

			auto position = getPosition() + sf::Vector2f{ xDeviation, yDeviation };

			auto food = Food::create(foodSize, position, sf::Color::Black);
			Environment::getInstance().insertNewFood(food);
		}
	}
}

bool Cell::isDead()
{
	return this->dead;
}

Genes& Cell::getGenes()
{
	return this->genes;
}

double Cell::getFoodLevel()
{
	return this->foodLevel;
}

double Cell::getCurrentSpeed()
{
	return this->currentSpeed;
}

void Cell::setCurrentSpeed(double speed)
{
	this->currentSpeed = speed;
}

void Cell::setFoodLevel(double foodLevel)
{
	this->foodLevel = foodLevel;
}

void Cell::setAge(double age)
{
	this->age = age;
}

void Cell::setHorniness(double horniness)
{
	this->horniness = horniness;
}
Ranged<double, 0, 100>& Cell::getHorniness()
{
	return this->horniness;
}
void Cell::dropRole(void(*role)(Cell *))
{
	auto newRolesEnd = std::remove_if(roles.begin(), roles.end(), [role](auto r) {return r == role; });
	roles.erase(newRolesEnd, roles.end());
}

void Cell::dropRoles()
{
	roles.clear();
}

void Cell::addRole(void(*role)(Cell *))
{
	roles.push_back(role);
}

std::string Cell::getSaveString()
{
	std::ostringstream result;

	result << getCellBlueprintString() <<
		VarAbbrv::currentRotation << ":" << this->getRotation() << " " <<
		VarAbbrv::currentPosition << ":{" << this->getPosition().x << ", " << this->getPosition().y << "} " <<
		VarAbbrv::color << ":{" <<
		static_cast<int>(this->getBaseColor().r) << ", " <<
		static_cast<int>(this->getBaseColor().g) << ", " <<
		static_cast<int>(this->getBaseColor().b) << ", " <<
		static_cast<int>(this->getBaseColor().a) << "} " <<
		VarAbbrv::currentAge << ":" << this->age << " " <<
		VarAbbrv::currentSpeed << ":" << this->currentSpeed << " " <<
		VarAbbrv::currentSize << ":" << this->getSize() << " " <<
		VarAbbrv::isDead << ":" << this->dead << " " <<
		VarAbbrv::currentFoodLevel << ":" << this->foodLevel << " " <<
		VarAbbrv::isFreezed << ":" << this->freezed << " " <<
		VarAbbrv::horniness << ":" << this->horniness << " " <<
		BaseObj::VarAbbrv::markedToDelete << ":" << this->isMarkedToDelete() << " " <<
		BaseObj::VarAbbrv::texture << ":" << TextureProvider::getInstance().getTextureName(this->shape.getTexture()) << " " <<
		VarAbbrv::cellRoles << ":{";

	if (roles.size() == 0)
		result << "0.0} ";
	else if (roles.size() > 0)
		result << CellRoles::getManager().getRoleId(roles.at(0));

	for (int i = 1; i < roles.size(); ++i)
		result << ", " << CellRoles::getManager().getRoleId(roles.at(i));
	result << "} ";


	return result.str();
}

std::string Cell::getCellBlueprintString()
{
	std::ostringstream result;

	result << "CELL-> " <<
		VarAbbrv::aggression << ":" << genes.aggresion << " " <<
		VarAbbrv::divisionTh << ":" << genes.divisionThreshold << " " <<
		VarAbbrv::foodLimit << ":" << genes.foodLimit << " " <<
		VarAbbrv::maxAge << ":" << genes.maxAge << " " <<
		VarAbbrv::maxSize << ":" << genes.maxSize << " " <<
		VarAbbrv::maxSpeed << ":" << genes.maxSpeed << " " <<
		VarAbbrv::radarRange << ":" << genes.radarRange << " ";

	return result.str();
}

std::shared_ptr<std::vector<std::shared_ptr<BaseObj>>> Cell::getFoodCollisionVector()
{
	auto& foodSectors = Environment::getInstance().getFoodCollisionSectors();
	const auto sectorsX = foodSectors.size();
	const auto sectorsY = foodSectors[0].size();

	auto cellPtr = this->getSelfPtr();
	auto cellPosition = Environment::getCollisionSectorCoords(cellPtr);

	auto minX = cellPosition.x - 1;
	if (minX < 0) minX = 0;

	auto minY = cellPosition.y - 1;
	if (minY < 0) minY = 0;

	auto maxX = cellPosition.x + 1;
	if (maxX >= sectorsX) maxX = sectorsX - 1;

	auto maxY = cellPosition.y + 1;
	if (maxY >= sectorsY) maxY = sectorsY - 1;

	//std::clog << minX << " " << minY << "   " << maxX << " " << maxY << std::endl;

	std::shared_ptr<std::vector<std::shared_ptr<BaseObj>>> result = std::make_shared<std::vector<std::shared_ptr<BaseObj>>>();

	for (int i = minX; i <= maxX; ++i)
	{
		for (int j = minY; j <= maxY; ++j)
		{
			for (auto& f : foodSectors[i][j])
			{
				if (cellPtr->collision(f) && !f->isMarkedToDelete())
				{
					result->push_back(f);
				}
			}
		}
	}
	return result;
}