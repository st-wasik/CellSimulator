#include "Cell.h"
#include "CellRoles.h"

Cell::Cell(float size, sf::Vector2f position)
{
	cell.setRadius(size);
	cell.setPosition(position);
	cell.setOrigin(size, size);
	cell.setRotation(static_cast<float>(randomReal(0, 359)));
	this->currentSpeed = randomReal(0.1, 2);
	cell.setFillColor(sf::Color::Green);

	// name of function is it's address
	// place here all roles-functions that cell should call
	roles.push_back(CellRoles::changeDirection);


	// make sure that moveForward is always the last role-function
	// cell should be moved after all updates
	roles.push_back(CellRoles::moveForward);
}

Cell::~Cell()
{
}

void Cell::update()
{
	for (auto& fn : roles)
	{
		fn(this);
	}
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cell, states);
}