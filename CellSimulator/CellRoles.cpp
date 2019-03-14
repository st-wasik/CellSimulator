#include "CellRoles.h"
#include "Random.h"
#include "Environment.h"
#include "Logger.h"
#include "CellSimApp.h"

void CellRoles::moveForward(Cell * c)
{
	const auto prevPosition = c->getPosition();

	c->cell.move(c->currentSpeed * std::sin((PI / 180)*c->getRotation()), c->currentSpeed * -std::cos((PI / 180)*c->getRotation()));

	while (!checkEnvironmentBounds(c))
	{
		c->cell.setPosition(prevPosition);
		c->cell.setRotation(c->getRotation() + 90);
		c->cell.move(c->currentSpeed * std::sin((PI / 180)*c->getRotation()), c->currentSpeed * -std::cos((PI / 180)*c->getRotation()));
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

bool CellRoles::checkEnvironmentBounds(Cell * c)
{
	const auto& envSize = Environment::getSize();
	const auto& cellPos = c->cell.getPosition();

	// if-else structure for future improvements - return collision bound

	//check left bound
	if (c->cell.getPosition().x - c->getSize() <= 0)
	{
		return false;
	}
	//check right bound
	else if (c->cell.getPosition().x + c->getSize() >= envSize.x)
	{
		return false;
	}
	//check top bound
	else if (c->cell.getPosition().y - c->getSize() <= 0)
	{
		return false;
	}
	//check bottom bound
	else if (c->cell.getPosition().y + c->getSize() >= envSize.y)
	{
		return false;
	}

	return true;
}
