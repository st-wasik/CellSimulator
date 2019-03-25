#pragma once
#include "Cell.h"

class CellRoles
{
public:
	CellRoles() = delete;

	static void moveForward(Cell* c);

	static void changeDirection(Cell* c);

	static void changeSpeed(Cell* c);

	static void eat(Cell* c);

	static void updateColor(Cell* c);

	static void beDead(Cell* c);

	void simulateHunger(Cell * c);

	/// \returns true if collision occured - otherwise false
	static bool checkEnvironmentBounds(Cell* c);
private:


};

