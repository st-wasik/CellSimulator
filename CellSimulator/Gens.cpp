#include "Gens.h"



Gens::Gens()
{
}


Gens::~Gens()
{
}

double & Gens::operator[](GensType genstype)
{
	switch (genstype)
	{
	case Gens::GensType::maxSpeed:
		return this->maxSpeed;
		break;
	case Gens::GensType::aggresion:
		return this->aggresion;
		break;
	case Gens::GensType::radarRange:
		return this->radarRange;
		break;
	case Gens::GensType::divisionThreshold:
		return this->divisionThreshold;
		break;
	case Gens::GensType::foodLimit:
		return this->foodLimit;
		break;
	case Gens::GensType::maxSize:
		return this->maxSize;
		break;
	case Gens::GensType::age:
		return this->age;
		break;
	default:
		return this->_default;
		break;
	}
}
