#include "Food.h"



Food::Food()
{
}

Food::Food(int radius, sf::Vector2f position, sf::Color color)
{
	Food::shape = sf::CircleShape(radius);
	Food::shape.setPosition(position);
	Food::shape.setFillColor(color);
}


Food::~Food()
{
}

void Food::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}