#include "Cell.h"

Cell::Cell() {

}

Cell::Cell(double size, sf::Vector2f position)
{
	cell.setRadius(size);
	cell.setPosition(position);
	cell.setOrigin(size, size);
	cell.setRotation(RandomReal(0, 359));
	this->currentSpeed = RandomReal(0.1, 2);
	cell.setFillColor(sf::Color::Green);
}

Cell::~Cell()
{
}

void Cell::update() 
{
	moveForward();
	if (RandomInt(0, 100) <= 50)
	{
		rotateLeft(RandomReal(-50, 0));
	}
	else
	{
		rotateRight(RandomReal(0, 50));
	}
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cell, states);
}

void Cell::moveForward()
{
	cell.move(this->currentSpeed * std::sin((PI / 180)*cell.getRotation()), this->currentSpeed * -std::cos((PI / 180)*cell.getRotation()));
}

void Cell::rotateLeft(double angle)
{
	cell.rotate(angle);

}

void Cell::rotateRight(double angle)
{
	cell.rotate(angle);
}