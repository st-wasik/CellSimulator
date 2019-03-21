#include "CellRoles.h"
#include "Random.h"
#include "Environment.h"
#include "Logger.h"
#include "CellSimApp.h"

constexpr double PI = 3.14159265358979323846;

void CellRoles::moveForward(Cell * c)
{
	const auto prevPosition = c->getPosition();
	auto moveSpeed = (Environment::getInstance().getTemperature() + 100) / 100 * c->currentSpeed;
	c->cell.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime());

	for (int attempt = 0; checkEnvironmentBounds(c); ++attempt)
	{
		c->cell.setPosition(prevPosition);
		c->cell.setRotation(c->getRotation() + 90);
		c->cell.move(moveSpeed * std::sin((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime(), moveSpeed * -std::cos((PI / 180)*c->getRotation()) * CellSimApp::getDeltaTime());
		
		if (attempt > 5) { c->setPosition(Environment::getInstance().getSize() / 2.f); break; }
	}
}

void CellRoles::changeDirection(Cell * c)
{
// DIRECTION CHANGE THRESHOLD SHOULD BE STORED IN GENES
	if(randomInt(0,100)>97)
		if (randomInt(0, 100) <= 50)
		{
			c->cell.rotate(randomReal(-50, 0));
		}
		else
		{
			c->cell.rotate(randomReal(0, 50));
		}
}

void CellRoles::changeSpeed(Cell * c)
{
// SPEED CHANGE THRESHOLD SHOULD BE STORED IN GENES
	if (randomInt(0, 1000) > 995)
		c->currentSpeed = randomReal(0.1, 2);
}

bool CellRoles::checkEnvironmentBounds(Cell * c)
{
	const auto& envSize = Environment::getInstance().getSize();
	const auto& cellPos = c->cell.getPosition();

	// if-else structure for future improvements - return collision bound

	//check left bound
	if (c->cell.getPosition().x - c->getSize() <= 0)
	{
		return true;
	}
	//check right bound
	else if (c->cell.getPosition().x + c->getSize() >= envSize.x)
	{
		return true;
	}
	//check top bound
	else if (c->cell.getPosition().y - c->getSize() <= 0)
	{
		return true;
	}
	//check bottom bound
	else if (c->cell.getPosition().y + c->getSize() >= envSize.y)
	{
		return true;
	}

	return false;
}
