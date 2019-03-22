#include "Cell.h"
#include "CellRoles.h"
#include "CellSimApp.h"

Cell::Cell(float size, sf::Vector2f position, sf::Color color) : BaseObj(size,position,color)
{
	this->foodLevel = 100;

	this->currentSpeed = randomReal(0.1, 2);

	shape.setOutlineColor(sf::Color::Yellow);
	//cell.setOutlineThickness(-1);

	// name of function is its address
	// place here all role-functions that cell should call
	roles.push_back(CellRoles::changeDirection);
	roles.push_back(CellRoles::changeSpeed);


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
	simulateHunger();
}

void Cell::simulateHunger() {
	this->foodLevel -= 0.01 * CellSimApp::getDeltaTime();
}

void Cell::freeze()
{
	freezed = true;
}

void Cell::unfreeze()
{
	freezed = false;
}
