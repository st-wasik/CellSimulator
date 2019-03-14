#include "Genes.h"



Genes::Genes()
{
}


Genes::~Genes()
{
}

double & Genes::operator[](GeneType GeneType)
{
	switch (GeneType)
	{
	case Genes::GeneType::maxSpeed:
		return this->maxSpeed;
		break;
	case Genes::GeneType::aggresion:
		return this->aggresion;
		break;
	case Genes::GeneType::radarRange:
		return this->radarRange;
		break;
	case Genes::GeneType::divisionThreshold:
		return this->divisionThreshold;
		break;
	case Genes::GeneType::foodLimit:
		return this->foodLimit;
		break;
	case Genes::GeneType::maxSize:
		return this->maxSize;
		break;
	case Genes::GeneType::age:
		return this->age;
		break;
	default:
		return this->_default;
		break;
	}
}
