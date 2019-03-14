#pragma once
#include "Cell.h"

constexpr double PI = 3.14159265358979323846;

class CellRoles
{
public:
	CellRoles() = delete;

	static void moveForward(Cell* c);

	static void changeDirection(Cell* c);
private:

	/// \returns false if collision occured - otherwise true
	static bool checkEnvironmentBounds(Cell* c);
};

