#include "Cell.h"
#include "CellRoles.h"
#include "CellSimApp.h"

Cell::Cell(float size, sf::Vector2f position) : freezed(false)
{
	setSize(size);
	setPosition(position);
	setRotation(static_cast<float>(randomReal(0, 359)));
	this->foodLevel = 100;

	this->currentSpeed = randomReal(0.1, 2);
	cell.setFillColor(sf::Color(randomInt(64, 255), randomInt(0, 64), randomInt(64, 255)));

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

std::string Cell::toString()
{
	return "Cell pos: " + (std::to_string(getPosition().x) + ":" + std::to_string(getPosition().y)) + " radius: " + std::to_string(getSize());
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
