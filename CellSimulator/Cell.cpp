#include "Cell.h"
#include "Food.h"
#include "CellRoles.h"
#include "CellSimApp.h"
#include "Environment.h"
#include "BaseObj.h"
#include "TextureProvider.h"

Cell::Cell(float size, sf::Vector2f position, sf::Color color) : BaseObj(size, position, color)
{
	this->foodLevel = 50;

	this->currentSpeed = randomReal(0.1, 2);

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
	//roles.push_back(CellRoles::grow);

	// make sure that moveForward is always the last role-function
	// cell should be moved after all updates
	roles.push_back(CellRoles::moveForward);
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
		auto& foodsVect = Environment::getInstance().getNewFoodsVector();

		for (int i = 0; i < foods; ++i)
		{
			float xDeviation = randomInt(-size/2, size/2);
			float yDeviation = randomInt(-size/2, size/2);

			auto position = getPosition() + sf::Vector2f{xDeviation, yDeviation};

			auto food = std::make_shared<Food>(Food(foodSize, position, getBaseColor()));
			foodsVect.push_back(food);
		}

	}
}

bool Cell::isDead()
{
	return this->dead;
}

Genes Cell::getGenes()
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

void Cell::dropRole(void(*role)(Cell *))
{
	auto newRolesEnd = std::remove_if(roles.begin(), roles.end(), [role](auto r) {return r == role; });
	roles.erase(newRolesEnd, roles.end());
}

void Cell::addRole(void(*role)(Cell *))
{
	roles.push_back(role);
}

bool Cell::collision(std::shared_ptr<BaseObj> obj)
{
	auto sizes = this->getSize() + obj->getSize();
	auto distance = this->getPosition() - obj->getPosition();
	if (distance.x * distance.x + distance.y*distance.y <= sizes * sizes)
	{
		return true;
	}
	return false;
}
