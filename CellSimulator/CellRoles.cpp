#include "CellRoles.h"
#include "Random.h"

void CellRoles::moveForward(Cell * c)
{
	const auto& rt = c->cell.getRotation();
	const auto& sd = c->currentSpeed;

	c->cell.move(sd * std::sin((PI / 180)*rt), sd * -std::cos((PI / 180)*rt));
}

void CellRoles::changeDirection(Cell * c)
{
	if (randomInt(0, 100) >= 95)
		if (randomInt(0, 100) <= 50)
		{
			c->cell.rotate(randomReal(-50, 0));
		}
		else
		{
			c->cell.rotate(randomReal(0, 50));
		}
}
