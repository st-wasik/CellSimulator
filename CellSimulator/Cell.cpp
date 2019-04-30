#include "Cell.h"
#include "Food.h"
#include "CellRoles.h"
#include "CellSimApp.h"
#include "Environment.h"
#include "BaseObj.h"
#include "RegexPattern.h"
#include "TextureProvider.h"
#include "MessagesManager.h"
#include <sstream>
#include <regex>

Cell::Cell() : BaseObj()
{
	age = 0;
	foodLevel = 0;
	currentSpeed = 0;
	horniness = 0;

	shape.setOutlineThickness(-5);
	shape.setOutlineColor(sf::Color(128, 64, 0, 75));
}

Cell::Cell(float size, sf::Vector2f position, sf::Color color) : BaseObj(size, position, color)
{
	this->age = 0;

	this->foodLevel = this->genes.foodLimit.get() / 2;

	this->currentSpeed = randomReal(0.1, genes.maxSpeed.get());

	this->horniness.randomize();

	shape.setOutlineColor(sf::Color::Yellow);


	int textureSize = getSize() / 1.3;
	shape.setTextureRect({ 0,0,textureSize, textureSize });
	shape.setTexture(TextureProvider::getInstance().getTexture("whiteNoise").get());

	shape.setOutlineThickness(-5);
	shape.setOutlineColor(sf::Color(128, 64, 0, 75));

	// name of function is its address
	// place here all role-functions that cell should call

	// make sure that checkCollisions is always the first role-function
	roles.push_back(CellRoles::checkCollisions);

	roles.push_back(CellRoles::changeDirection);
	roles.push_back(CellRoles::sniffForFood);
	roles.push_back(CellRoles::changeSpeed);
	roles.push_back(CellRoles::eat);
	roles.push_back(CellRoles::updateColor);
	roles.push_back(CellRoles::simulateHunger);
	roles.push_back(CellRoles::divideAndConquer);
	roles.push_back(CellRoles::getingHot);
	roles.push_back(CellRoles::grow);
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

Cell::Cell(std::string formattedCellString) : Cell()
{
	static std::regex cellRegex("CELL->( " + RegexPattern::Word + ":((" + RegexPattern::Double + ")|(" + RegexPattern::Vector + ")|(" + RegexPattern::Word + ")))* ");
	if (!std::regex_match(formattedCellString.begin(), formattedCellString.end(), cellRegex))
	{
		Logger::log("Cell string wrong format!");
		return;
	}

	std::regex settingRegex(" " + RegexPattern::Word + ":((" + RegexPattern::Double + ")|(" + RegexPattern::Vector + ")|" + RegexPattern::Word + ")");

	auto settingsBegin = std::sregex_iterator(formattedCellString.begin(), formattedCellString.end(), settingRegex);
	auto settingsEnd = std::sregex_iterator();

	for (auto i = settingsBegin; i != settingsEnd; ++i)
	{
		std::string settingStr = i->str();
		static std::regex type(RegexPattern::Word);
		static std::regex value(RegexPattern::Double);
		static std::regex vectorValue(RegexPattern::Vector);

		auto type_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), type);

		auto vector_value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), vectorValue);

		if (std::distance(type_i, std::sregex_iterator()) == 2)
		{
			auto val = type_i;
			++val;
			modifyValueFromString(type_i->str(), val->str());
		}
		else if (type_i != std::sregex_iterator() && vector_value_i != std::sregex_iterator())
		{
			std::regex value(RegexPattern::Double);
			auto vector_value_s = vector_value_i->str();
			auto valuesBegin = std::sregex_iterator(vector_value_s.begin(), vector_value_s.end(), value);
			std::vector<std::string> values_vect;
			for (auto it = valuesBegin; it != std::sregex_iterator(); it++)
			{
				values_vect.push_back(it->str());
			}
			modifyValueFromVector(type_i->str(), values_vect);
		}
		else
		{
			auto value_i = std::sregex_iterator(settingStr.begin(), settingStr.end(), value);
			if (type_i != std::sregex_iterator() && value_i != std::sregex_iterator())
				modifyValueFromString(type_i->str(), value_i->str());
		}

		//TODO: add cell name
	}
	CellRoles::updateColor(this);
}

void Cell::modifyValueFromString(std::string valueName, std::string value)
{
	//Logger::log("Setting '" + valueName + "' to " + value);
	auto& v = valueName;

	if (v == VarAbbrv::currentRotation)			this->setRotation(std::stod(value));
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
	else if (v == VarAbbrv::metabolism)			this->genes.metabolism = (std::stod(value));
	else if (v == BaseObj::VarAbbrv::texture)			this->shape.setTexture(TextureProvider::getInstance().getTexture(value).get());
	else if (v == BaseObj::VarAbbrv::markedToDelete)
	{
		if (std::stod(value)) this->markToDelete();
	}
	else Logger::log(std::string("Unknown cell var name '" + v + "' with value '" + value + "'!"));
}

void Cell::modifyValueFromVector(std::string valueName, const std::vector<std::string>& values)
{
	//Logger::log("Setting '" + valueName + "'.");
	auto& v = valueName;

	if (v == VarAbbrv::currentPosition)
	{
		if (values.size() != 2)
		{
			Logger::log("Wrong values count for " + std::string(VarAbbrv::currentPosition) + ": " + std::to_string(values.size()) + ".");
			return;
		}
		this->setPosition(sf::Vector2f(std::stod(values[0]), std::stod(values[1])));
	}
	else if (v == VarAbbrv::color)
	{
		if (values.size() != 4)
		{
			Logger::log("Wrong values count for " + std::string(VarAbbrv::color) + ": " + std::to_string(values.size()) + ". <" + values[0] + ">");
			return;
		}
		this->setBaseColor(sf::Color(std::stod(values[0]), std::stod(values[1]), std::stod(values[2]), std::stod(values[3])));
	}
	else if (v == BaseObj::VarAbbrv::textureRect)
	{
		if (values.size() != 4)
		{
			Logger::log("Wrong values count for " + std::string(BaseObj::VarAbbrv::textureRect) + ".");
			return;
		}
		this->shape.setTextureRect(sf::IntRect(std::stod(values[0]), std::stod(values[1]), std::stod(values[2]), std::stod(values[3])));
	}
	else if (v == VarAbbrv::cellRoles)
	{
		for (int i = 0; i < values.size(); ++i)
		{
			this->addRole(CellRoles::getManager().getRoleById(std::stod(values.at(i))));
		}
	}
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

	auto color = getBaseColor();
	color.a = 128;
	shape.setFillColor(color);
}

void Cell::unfreeze()
{
	auto color = getBaseColor();
	color.a = 255;
	shape.setFillColor(color);

	freezed = false;
}

void Cell::kill()
{
	if (!dead)
	{
		if (!name.empty()) MessagesManager::getInstance().append(name + " died [*].");

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
	if (std::find(roles.begin(), roles.end(), role) == roles.end())
		roles.push_back(role);
}

std::string Cell::getSaveString()
{
	std::ostringstream result;

	result << getCellBlueprintString() <<
		VarAbbrv::currentRotation << ":" << this->getRotation() << " " <<
		VarAbbrv::currentPosition << ":{" << this->getPosition().x << ", " << this->getPosition().y << "} " <<
		VarAbbrv::currentAge << ":" << this->age << " " <<
		VarAbbrv::currentSpeed << ":" << this->currentSpeed << " " <<
		VarAbbrv::currentSize << ":" << this->getSize() << " " <<
		VarAbbrv::isDead << ":" << this->dead << " " <<
		VarAbbrv::currentFoodLevel << ":" << this->foodLevel << " " <<
		VarAbbrv::isFreezed << ":" << this->freezed << " " <<
		VarAbbrv::horniness << ":" << this->horniness << " " <<
		BaseObj::VarAbbrv::markedToDelete << ":" << this->isMarkedToDelete() << " " <<
		VarAbbrv::color << ":{" <<
		static_cast<int>(this->getBaseColor().r) << ", " <<
		static_cast<int>(this->getBaseColor().g) << ", " <<
		static_cast<int>(this->getBaseColor().b) << ", " <<
		static_cast<int>(this->getBaseColor().a) << "} " <<
		BaseObj::VarAbbrv::textureRect << ":{" << this->shape.getTextureRect().left << ", " <<
		this->shape.getTextureRect().top << ", " <<
		this->shape.getTextureRect().width << ", " <<
		this->shape.getTextureRect().height << "} " <<
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
		VarAbbrv::radarRange << ":" << genes.radarRange << " " <<
		VarAbbrv::metabolism << ":" << genes.metabolism << " ";
	return result.str();
}

std::string Cell::getName()
{
	return name;
}

void Cell::setName(std::string n)
{
	name = n;
}

void Cell::setMakedFoodColor(sf::Color c)
{
	makedFoodColor = c;
}

sf::Color Cell::getMakedFoodColor()
{
	return makedFoodColor;
}

void Cell::getFoodCollisionVector()
{
	this->FoodCollisionVector->clear();
	auto& foodSectors = Environment::getInstance().getFoodCollisionSectors();
	const auto sectorsX = foodSectors.size();
	const auto sectorsY = foodSectors[0].size();

	auto cellPtr = this->getSelfPtr();
	auto cellPosition = Environment::getCollisionSectorCoords(cellPtr);

	auto minX = cellPosition.x - static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (minX < 0) minX = 0;

	auto minY = cellPosition.y - static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (minY < 0) minY = 0;

	auto maxX = cellPosition.x + static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (maxX >= sectorsX) maxX = sectorsX - 1;

	auto maxY = cellPosition.y + static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (maxY >= sectorsY) maxY = sectorsY - 1;

	//std::clog << minX << " " << minY << "   " << maxX << " " << maxY << std::endl;

	//250000 is a max distance^2 what cell can "see"
	double distance = 250000;
	for (int i = minX; i <= maxX; ++i)
	{
		for (int j = minY; j <= maxY; ++j)
		{
			for (auto& food : foodSectors[i][j])
			{
				auto check = cellPtr->collision(food);
				if (check.second < distance && !food->isMarkedToDelete())
				{
					this->closestFood.first = food;
					this->closestFood.second = distance = check.second;
				}
				if (check.first && !food->isMarkedToDelete())
				{
					this->FoodCollisionVector->push_back(food);
				}
			}
		}
	}
}

void Cell::getCellCollisionVector()
{
	this->CellCollisionVector->clear();
	auto& cellSectors = Environment::getInstance().getCellCollisionSectors();
	const auto sectorsX = cellSectors.size();
	const auto sectorsY = cellSectors[0].size();

	auto cellPtr = this->getSelfPtr();
	auto cellPosition = Environment::getCollisionSectorCoords(cellPtr);

	auto minX = cellPosition.x - static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (minX < 0) minX = 0;

	auto minY = cellPosition.y - static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (minY < 0) minY = 0;

	auto maxX = cellPosition.x + static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (maxX >= sectorsX) maxX = sectorsX - 1;

	auto maxY = cellPosition.y + static_cast<int>(this->genes.radarRange.get() / 50 + 0.5);
	if (maxY >= sectorsY) maxY = sectorsY - 1;

	//std::clog << minX << " " << minY << "   " << maxX << " " << maxY << std::endl;

	//250000 is a max distance^2 what cell can "see"
	double distance = 250000;
	for (int i = minX; i <= maxX; ++i)
	{
		for (int j = minY; j <= maxY; ++j)
		{
			for (auto& cell : cellSectors[i][j])
			{
				auto check = cellPtr->collision(cell);
				if (check.second < distance && !cell->isMarkedToDelete())
				{
					this->closestCell.first = cell;
					this->closestCell.second = distance = check.second;
				}
				if (check.first && !cell->isMarkedToDelete())
				{
					this->CellCollisionVector->push_back(std::dynamic_pointer_cast<Cell>(cell));
				}
			}
		}
	}
}
