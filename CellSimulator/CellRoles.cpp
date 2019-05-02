#include "CellRoles.h"
#include "Random.h"
#include "Environment.h"
#include "Logger.h"
#include "CellSimApp.h"
#include "CellSelectionTool.h"
#include "Distance.h"
#include "RangeChecker.h"
constexpr double PI = 3.14159265358979323846;

#define VAR_NAME(v) #v

CellRoles::RolePtr CellRoles::getRoleById(int id)
{
	return idToRole[id];
}

int CellRoles::getRoleId(RolePtr ptr)
{
	return roleToId[ptr];
}

// REGISTER ALL NEW ADDED ROLES - needed to save cell to file
CellRoles::CellRoles()
{
	// to disable 'registering cellrole' logs simply change #v to "" in #define VAR_NAME(v)

	registerRole(moveForward, 0, VAR_NAME(moveForward));
	registerRole(changeDirection, 1, VAR_NAME(changeDirection));
	registerRole(eat, 2, VAR_NAME(eat));
	registerRole(updateColor, 3, VAR_NAME(updateColor));
	registerRole(beDead, 4, VAR_NAME(beDead));
	registerRole(simulateHunger, 5, VAR_NAME(simulateHunger));
	registerRole(divideAndConquer, 6, VAR_NAME(divideAndConquer));
	registerRole(grow, 7, VAR_NAME(grow));
	registerRole(getingHot, 8, VAR_NAME(getingHot));
	registerRole(makeFood, 9, VAR_NAME(makeFood));
	registerRole(fight, 10, VAR_NAME(fight));
	registerRole(makeOlder, 11, VAR_NAME(makeOlder));
	registerRole(mutate, 12, VAR_NAME(mutate));
	registerRole(changeSpeed, 13, VAR_NAME(changeSpeed));
	registerRole(sniffForFood, 14, VAR_NAME(sniffForFood));
	registerRole(sniffForCell, 15, VAR_NAME(sniffForCell));
	registerRole(checkCollisions, 16, VAR_NAME(checkCollisions));
}

CellRoles & CellRoles::getManager()
{
	static CellRoles instance;
	return instance;
}


void CellRoles::moveForward(Cell * c)
{
	auto cellPtr = c->getSelfPtr();
	const auto prevPosition = c->getPosition();
	const auto prevCollisionSectorCoords = Environment::getCollisionSectorCoords(cellPtr);

	auto moveSpeed = (Environment::getInstance().getTemperature() + 100) / 100 * c->currentSpeed;
	c->shape.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime());

	for (int attempt = 0; checkEnvironmentBounds(c); ++attempt)
	{
		c->shape.setPosition(prevPosition);
		c->shape.setRotation(c->getRotation() + 90);
		c->shape.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime());

		if (attempt > 5) { c->setPosition(Environment::getInstance().getSize() / 2.f); break; }
	}

	// update collision sectors
	const auto currentCollisionSectorCoords = Environment::getCollisionSectorCoords(c->getSelfPtr());
	if (prevCollisionSectorCoords != currentCollisionSectorCoords)
	{
		auto& sectors = Environment::getInstance().getCellCollisionSectors();
		auto& prevCVect = sectors[prevCollisionSectorCoords.x][prevCollisionSectorCoords.y];
		auto& currCVect = sectors[currentCollisionSectorCoords.x][currentCollisionSectorCoords.y];

		prevCVect.erase(std::remove(prevCVect.begin(), prevCVect.end(), cellPtr), prevCVect.end());
		currCVect.push_back(cellPtr);
	}
}

void CellRoles::changeDirection(Cell * c)
{
	if (randomInt(0, 100) > 97)
	{
		if (randomInt(0, 100) <= 50)
		{
			c->shape.rotate(randomReal(-25, 0));
		}
		else
		{
			c->shape.rotate(randomReal(0, 25));
		}
	}
}

void CellRoles::changeSpeed(Cell * c)
{
	// SPEED CHANGE THRESHOLD SHOULD BE STORED IN GENES
	if (randomInt(0, 1000) > 995)
		c->currentSpeed = randomReal(0.1, static_cast<float>(c->genes.maxSpeed.get()));
}

void CellRoles::eat(Cell * c)
{
	auto& foods = Environment::getInstance().getFoodsVector();
	auto& collisions = c->FoodCollisionVector;

	for (auto& f : *collisions)
	{
		if (c->foodLevel < c->genes.foodLimit.get())
		{
			c->foodLevel += static_cast<float>(f->getSize());
			f->markToDelete();
		}
	}
}

void CellRoles::updateColor(Cell * c)
{
	static double threshold = 30;

	Ranged<int, 0, 255> newR, newG, newB;

	auto newColor = c->getBaseColor();

	//temperature
	auto& envTemp = Environment::getInstance().getTemperature();
	auto& envRad = Environment::getInstance().getRadiation();
	if (envTemp > threshold)
	{
		newR = 2 * abs(envTemp - threshold) + c->getBaseColor().r;
		newColor.r = newR.get();
	}
	else if (envTemp < -threshold)
	{
		newB = 2 * abs(envTemp + threshold) + c->getBaseColor().b;
		newColor.b = newB.get();
	}

	//radiation
	if (envRad > threshold)
	{
		newG = 3 * abs(envRad - threshold) + c->getBaseColor().g;
		newColor.g = newG.get();
	}

	c->shape.setFillColor(newColor);
}

void CellRoles::beDead(Cell * c)
{
	auto color = c->shape.getFillColor();
	if (color.a > 0)
	{
		double a = static_cast<double>(color.a) - ((Environment::getInstance().getTemperature() + 100 + 1)*0.01*CellSimApp::getInstance().getDeltaTime());
		if (0 > a) a = 0;
		color.a = a;
		c->shape.setFillColor(color);
	}
	else
	{
		c->markToDelete();
	}
}

void CellRoles::simulateHunger(Cell * c) {
	c->foodLevel -= 0.025 * CellSimApp::getInstance().getDeltaTime() * c->genes.metabolism.get() * c->currentSpeed * c->getSize() / 10;
	if (c->foodLevel <= 0)
	{
		c->kill();
	}
}

void CellRoles::divideAndConquer(Cell * c)
{
	auto& cells = Environment::getInstance().getCellsVector();
	if (c->foodLevel >= c->genes.foodLimit.get() && c->getSize() >= c->genes.maxSize.get() && randomInt(0, 100) <= c->genes.divisionThreshold.get())
	{
		c->foodLevel -= c->genes.foodLimit.get() / 2;
		c->setSize(c->genes.maxSize.get() / 2);
		auto ptr = Cell::create(*c);
		Environment::getInstance().insertNewCell(ptr);
		c->setRotation(c->getRotation() + 180);
	}
}

void CellRoles::grow(Cell * c)
{
	auto rand = randomReal(0.0005, 0.025);

	auto prevSize = c->getSize();

	// grow
	if (c->getSize() < c->genes.maxSize.get() && c->foodLevel >= c->genes.foodLimit.get()*0.90)
	{
		c->setSize(c->getSize() + (rand * CellSimApp::getInstance().getDeltaTime()));
		if (checkEnvironmentBounds(c))
		{
			c->setSize(prevSize);
		}
	}
	// grow in other direction
	else if (c->getSize() > 15 && c->foodLevel <= c->genes.foodLimit.get()*0.25)
	{
		c->setSize(c->getSize() - (rand * CellSimApp::getInstance().getDeltaTime()));
	}
}

void CellRoles::getingHot(Cell * c)
{
	if (c->foodLevel >= c->genes.foodLimit.get()*0.75)
	{
		c->setHorniness(c->getHorniness().get() + (randomReal(0.01, 0.05)*CellSimApp::getInstance().getDeltaTime()));
	}
	if (c->horniness.isMax())
	{
		auto & cells = c->CellCollisionVector;
		for (auto & cell : *cells)
		{
			if (cell.get() != c && !cell->isDead() && cell->getHorniness().isMax() && c->genes.type.get() == cell->genes.type.get())
			{
				c->setHorniness(0);
				c->foodLevel = c->genes.foodLimit.get() / 2;
				cell->setHorniness(0);
				cell->foodLevel = c->genes.foodLimit.get() / 2;
				std::shared_ptr<Cell> tmp = Cell::create(*c, *cell);
				Environment::getInstance().insertNewCell(tmp);
			}
		}
	}
}

void CellRoles::makeFood(Cell * c)
{
	c->foodLevel += randomReal(0.1, 0.5) * c->genes.metabolism.get() * CellSimApp::getInstance().getDeltaTime();

	if (c->foodLevel >= c->genes.foodLimit.get())
	{
		c->foodLevel = 0;
		auto size = c->getSize();

		int foods = randomInt(0, 100) > 70 ? 2 : 1;
		auto foodSize = 0.5 * size;

		for (int i = 0; i < foods; ++i)
		{
			float xDeviation = randomInt(-size / 2, size / 2);
			float yDeviation = randomInt(-size / 2, size / 2);

			auto position = c->getPosition() + sf::Vector2f{ xDeviation, yDeviation };

			constexpr int margin = 8;
			auto foodColor = c->makedFoodColor;
			foodColor.r = randomInt(foodColor.r - margin, foodColor.r + margin);
			foodColor.g = randomInt(foodColor.g - margin, foodColor.g + margin);
			foodColor.b = randomInt(foodColor.b - margin, foodColor.b + margin);
			auto food = Food::create(foodSize, position, foodColor);
			Environment::getInstance().insertNewFood(food);

			c->horniness = 0;
		}
	}

}

void CellRoles::fight(Cell * c)
{
	std::vector<std::shared_ptr<Cell>> cells = Environment::getInstance().getCellsVector();

	for (auto& cell : cells)
	{
		if (c->collision(cell).first && c != cell.get())
		{
			float cSize = c->getSize();
			float cellSize = cell->getSize();
			int sizeDelta = 2;

			if (cSize > cellSize) {
				c->setSize(cSize - sizeDelta);
				cell->setSize(cellSize + sizeDelta);
				cell->foodLevel += sizeDelta;
			}
			else if (cSize < cellSize) {
				c->setSize(cSize + sizeDelta);
				c->foodLevel += sizeDelta;
				cell->setSize(cellSize - sizeDelta);
			}

			double cCurrentSpeed = c->getCurrentSpeed();
			double cellCurrentSpeed = cell->getCurrentSpeed();

			c->setRotation(c->getRotation() + 180);
			c->shape.move(cCurrentSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime(), cCurrentSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getInstance().getDeltaTime());
			cell->setRotation(c->getRotation() + 180);
			cell->shape.move(cellCurrentSpeed * std::sin((PI / 180)*cell->getRotation()) * CellSimApp::getInstance().getDeltaTime(), cellCurrentSpeed * -std::cos((PI / 180)*cell->getRotation()) * CellSimApp::getInstance().getDeltaTime());
		}
	}
}

void CellRoles::makeOlder(Cell * c)
{
	if (c->age >= c->genes.maxAge.get())
	{
		c->kill();
		return;
	}
	c->age += CellSimApp::getInstance().getDeltaTime()*0.01;
}

void CellRoles::mutate(Cell * c)
{
	if (randomInt(0, 100) > 99) {

		constexpr double mutationRatio = 100;

		auto& genes = c->getGenes();
		genes.aggresion = genes.aggresion + genes.aggresion.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.divisionThreshold = genes.divisionThreshold + genes.divisionThreshold.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.foodLimit = genes.foodLimit + genes.foodLimit.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.maxAge = genes.maxAge + genes.maxAge.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.maxSize = genes.maxSize + genes.maxSize.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.maxSpeed = genes.maxSpeed + genes.maxSpeed.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.radarRange = genes.radarRange + genes.radarRange.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		genes.metabolism = genes.metabolism + genes.metabolism.getRange() / mutationRatio * Environment::getInstance().getRadiation() * randomInt(-1, 1);
		c->setFoodLevel(checkRange(c->getFoodLevel(), 0, genes.foodLimit.get()));
		c->setAge(checkRange(c->age, 0, genes.maxAge.get()));
		c->setSize(checkRange(c->getSize(), 15, genes.maxSize.get()));
		c->setCurrentSpeed(checkRange(c->getCurrentSpeed(), 0, genes.maxSpeed.get()));
	}

}

void CellRoles::sniffForFood(Cell * c)
{
	if (c->foodLevel <= c->genes.foodLimit.get()*0.8 && c->closestFood.first != nullptr && c->closestFood.second <= c->genes.radarRange.get()*c->genes.radarRange.get() + c->getSize())
	{
		auto v = c->closestFood.first->getPosition() - c->getPosition();
		auto angle = atan2(v.y, v.x);
		double angle_change = c->genes.turningRate.get() * CellSimApp::getInstance().getDeltaTime();
		angle = angle * (180 / PI);
		if (angle < 0)
		{
			angle = 360 - (-angle);
		}
		angle += 90; //Remove this for some magic
		double cfDiffrence = c->getRotation() - angle;
		double abscfDiffrence = abs(cfDiffrence);
		if (abscfDiffrence > 180)
		{
			if (360 - abscfDiffrence < angle_change)
			{
				c->shape.rotate(cfDiffrence <= 0 ? -(360 - abscfDiffrence)*CellSimApp::getInstance().getDeltaTime() : (360 - abscfDiffrence)*CellSimApp::getInstance().getDeltaTime());
			}
			else
			{
				c->shape.rotate(cfDiffrence <= 0 ? -angle_change : angle_change);
			}
		}
		else
		{
			if (abscfDiffrence < angle_change)
			{
				c->shape.rotate(cfDiffrence >= 0 ? -abscfDiffrence * CellSimApp::getInstance().getDeltaTime() : abscfDiffrence * CellSimApp::getInstance().getDeltaTime());
			}
			else
			{
				c->shape.rotate(cfDiffrence >= 0 ? -angle_change : angle_change);
			}
		}
	}
}

void CellRoles::checkCollisions(Cell * c)
{
	c->FoodCollisionVector->clear();
	c->CellCollisionVector->clear();
	c->closestFood.first = nullptr;
	c->closestCell.first = nullptr;
	c->closestFood.second = -1;
	c->closestCell.second = -1;
	if (c->genes.type.get() != 2)
	{
		c->getFoodCollisionVector();
	}
	if (c->genes.type.get() != 1)
	{
		c->getCellCollisionVector();
	}
}

void CellRoles::sniffForCell(Cell * c)
{
	if (c->foodLevel <= c->genes.foodLimit.get()*0.8 && c->closestCell.first != nullptr && c->closestCell.second <= c->genes.radarRange.get()*c->genes.radarRange.get() + c->getSize())
	{
		auto v = c->closestCell.first->getPosition() - c->getPosition();
		auto angle = atan2(v.y, v.x);
		double angle_change = c->genes.turningRate.get() * CellSimApp::getInstance().getDeltaTime();
		angle = angle * (180 / PI);
		if (angle < 0)
		{
			angle = 360 - (-angle);
		}
		angle += 90; //Remove this for some magic
		double cfDiffrence = c->getRotation() - angle;
		double abscfDiffrence = abs(cfDiffrence);
		if (abscfDiffrence > 180)
		{
			if (360 - abscfDiffrence < angle_change)
			{
				c->shape.rotate(cfDiffrence <= 0 ? -(360 - abscfDiffrence)*CellSimApp::getInstance().getDeltaTime() : (360 - abscfDiffrence)*CellSimApp::getInstance().getDeltaTime());
			}
			else
			{
				c->shape.rotate(cfDiffrence <= 0 ? -angle_change : angle_change);
			}
		}
		else
		{
			if (abscfDiffrence < angle_change)
			{
				c->shape.rotate(cfDiffrence >= 0 ? -abscfDiffrence * CellSimApp::getInstance().getDeltaTime() : abscfDiffrence * CellSimApp::getInstance().getDeltaTime());
			}
			else
			{
				c->shape.rotate(cfDiffrence >= 0 ? -angle_change : angle_change);
			}
		}
	}
}

bool CellRoles::checkEnvironmentBounds(Cell * c)
{
	const auto& envSize = Environment::getInstance().getSize();
	const auto& cellPos = c->shape.getPosition();

	// if-else structure for future improvements - return collision bound

	//check left bound
	if (c->shape.getPosition().x - c->getSize() <= 0)
	{
		return true;
	}
	//check right bound
	else if (c->shape.getPosition().x + c->getSize() >= envSize.x)
	{
		return true;
	}
	//check top bound
	else if (c->shape.getPosition().y - c->getSize() <= 0)
	{
		return true;
	}
	//check bottom bound
	else if (c->shape.getPosition().y + c->getSize() >= envSize.y)
	{
		return true;
	}

	return false;
}

void CellRoles::registerRole(RolePtr ptr, int id, std::string roleName)
{
	roleToId[ptr] = id;
	idToRole[id] = ptr;

	if (!roleName.empty())
		Logger::log(std::string("Registering Cell Role " + roleName + " with ID ") + std::to_string(id));
}
