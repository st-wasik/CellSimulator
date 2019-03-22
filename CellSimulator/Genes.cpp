#include "Genes.h"

Genes::Genes()
{
}

Genes::Genes(double maxSpeed, double aggresion, double radarRange, double divisionThreshold, double foodLimit, double maxSize, double age)
{
	this->maxSize = maxSize;
	this->aggresion = aggresion;
	this->radarRange = radarRange;
	this->divisionThreshold = divisionThreshold;
	this->foodLimit = foodLimit;
	this->maxSize = maxSize;
	this->age = age;
}
