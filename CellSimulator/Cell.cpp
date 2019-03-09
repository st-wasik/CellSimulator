#include "Cell.h"

Cell::Cell() {

}

Cell::Cell(double size, sf::Vector2f position)
{
	cell.setRadius(size);
	cell.setPosition(position);
	cell.setFillColor(sf::Color::Green);
}

Cell::~Cell()
{
}

void Cell::update() {

	
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cell, states);
}