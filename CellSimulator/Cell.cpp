#include "Cell.h"
#include "Food.h"
#include "CellRoles.h"
#include "CellSimApp.h"
#include "Environment.h"
#include "BaseObj.h"
#include "TextureProvider.h"

Cell::Cell(float size, sf::Vector2f position, sf::Color color) : BaseObj(size, position, color)
{
	this->age = 0;

	this->foodLevel = 50;

	this->currentSpeed = randomReal(0.1, 2);

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
	//roles.push_back(CellRoles::divideAndConquer);
	roles.push_back(CellRoles::getingHot);
	//roles.push_back(CellRoles::grow);
	//roles.push_back(CellRoles::fight);
	roles.push_back(CellRoles::makeOlder);
	// make sure that moveForward is always the last role-function
	// cell should be moved after all updates
	roles.push_back(CellRoles::moveForward);
}

Cell::Cell(Cell a, Cell b) : Cell(10,(a.getPosition()+b.getPosition())/2.0f, a.baseColor*b.baseColor)
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
