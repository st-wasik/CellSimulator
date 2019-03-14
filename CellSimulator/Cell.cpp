#include "Cell.h"
#include "CellRoles.h"

Cell::Cell(float size, sf::Vector2f position)
{
	setSize(size);
	setPosition(position);
	setRotation(static_cast<float>(randomReal(0, 359)));

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

float Cell::getSize()
{
	return cell.getRadius();
}

void Cell::setSize(const float & s)
{
	cell.setRadius(s);
	cell.setOrigin(s, s);
}

float Cell::getRotation()
{
	return cell.getRotation();
}

void Cell::setRotation(const float & r)
{
	cell.setRotation(r);
}

sf::Vector2f Cell::getPosition()
{
	return cell.getPosition();
}

void Cell::setPosition(const sf::Vector2f & p)
{
	cell.setPosition(p);
}
