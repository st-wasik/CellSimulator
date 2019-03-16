#pragma once
#include "Cell.h"

constexpr double PI = 3.14159265358979323846;

class CellRoles
{
public:
	CellRoles() = delete;

	static void moveForward(Cell* c);

	static void changeDirection(Cell* c);

	static void changeSpeed(Cell* c);

	/// \returns true if collision occured - otherwise false
	static bool checkEnvironmentBounds(Cell* c);
private:


};

