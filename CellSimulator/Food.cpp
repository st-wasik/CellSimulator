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
		VarAbbrv::currentPositionX << ":" << this->getPosition().x << " " <<
		VarAbbrv::currentPositionY << ":" << this->getPosition().y << " " <<
		VarAbbrv::colorR << ":" << static_cast<int>(this->getBaseColor().r) << " " <<
		VarAbbrv::colorG << ":" << static_cast<int>(this->getBaseColor().g) << " " <<
		VarAbbrv::colorB << ":" << static_cast<int>(this->getBaseColor().b) << " " <<
		VarAbbrv::colorA << ":" << static_cast<int>(this->getBaseColor().a) << " " <<
		VarAbbrv::currentSize << ":" << this->getSize() << " " <<
		VarAbbrv::markedToDelete << ":" << this->isMarkedToDelete() << " ";

	return result.str();
}
