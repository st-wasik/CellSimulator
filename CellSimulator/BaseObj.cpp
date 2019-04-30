#include "BaseObj.h"



BaseObj::BaseObj()
{
	setSize(20);
	setPosition({ 0, 0 });
	setRotation(0);
	shape.setFillColor(sf::Color::White);
}

BaseObj::BaseObj(float size, sf::Vector2f position, sf::Color color) : toDelete(false), baseColor(color)
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

sf::Color BaseObj::getBaseColor()
{
	return baseColor;
}

void BaseObj::setBaseColor(sf::Color c, bool update)
{
	baseColor = c;
	//if (update)
	shape.setFillColor(c);
}

float BaseObj::getOutlineThickness()
{
	return shape.getOutlineThickness();
}

void BaseObj::setOutlineThickness(float v)
{
	shape.setOutlineThickness(v);
}

std::string BaseObj::toString()
{
	return "Object pos: " + (std::to_string(getPosition().x) + ":" + std::to_string(getPosition().y)) + " radius: " + std::to_string(getSize()) + " rotation:" + std::to_string(getRotation());
}

void BaseObj::markToDelete()
{
	toDelete = true;
}

bool BaseObj::isMarkedToDelete()
{
	return toDelete;
}

std::pair<bool, double> BaseObj::collision(std::shared_ptr<BaseObj> obj)
{
	auto sizes = this->getSize() + obj->getSize();
	auto subPosition = this->getPosition() - obj->getPosition();
	double distance = subPosition.x*subPosition.x + subPosition.y*subPosition.y;
	if (distance <= sizes * sizes)
	{
		return std::make_pair(true, distance);
	}
	return std::make_pair(false, distance);
}

void BaseObj::setSelfPtr(std::shared_ptr<BaseObj> s)
{
	self = s;
}

std::shared_ptr<BaseObj> BaseObj::getSelfPtr()
{
	return self;
}
