#include "Food.h"
#include <sstream>

Food::Food(float size, sf::Vector2f position, sf::Color color) : BaseObj(size, position, color)
{
}

Food::~Food()
{
}

void Food::update()
{
}

std::string Food::getSaveString()
{
	std::ostringstream result;

	result << "FOOD-> " <<
		VarAbbrv::currentRotation << ":" << this->getRotation() << " " <<
		VarAbbrv::currentPosition << ":{" << this->getPosition().x << ", " << this->getPosition().y << "} " <<
		VarAbbrv::color << ":{" <<
		static_cast<int>(this->getBaseColor().r) << ", " <<
		static_cast<int>(this->getBaseColor().g) << ", " <<
		static_cast<int>(this->getBaseColor().b) << ", " <<
		static_cast<int>(this->getBaseColor().a) << "} " <<
		VarAbbrv::currentSize << ":" << this->getSize() << " " <<
		VarAbbrv::markedToDelete << ":" << this->isMarkedToDelete() << " ";

	return result.str();
}
