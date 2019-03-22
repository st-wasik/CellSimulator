#include "BaseObj.h"



BaseObj::BaseObj(float size, sf::Vector2f position, sf::Color color)
{
	setSize(size);
	setPosition(position);
	setRotation(static_cast<float>(randomReal(0, 359)));
	this->shape.setFillColor(color);
}


BaseObj::~BaseObj()
{
}


void BaseObj::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

float BaseObj::getSize()
{
	return shape.getRadius();
}

void BaseObj::setSize(const float & s)
{
	shape.setRadius(s);
	shape.setOrigin(s, s);
}

float BaseObj::getRotation()
{
	return shape.getRotation();
}

void BaseObj::setRotation(const float & r)
{
	shape.setRotation(r);
}

sf::Vector2f BaseObj::getPosition()
{
	return shape.getPosition();
}

void BaseObj::setPosition(const sf::Vector2f & p)
{
	shape.setPosition(p);
}

std::string BaseObj::toString()
{
	return "Object pos: " + (std::to_string(getPosition().x) + ":" + std::to_string(getPosition().y)) + " radius: " + std::to_string(getSize());
}