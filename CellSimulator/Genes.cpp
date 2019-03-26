#include "Genes.h"

Genes::Genes()
{
	randomize();
}

Genes::Genes(double maxSpeed, double aggresion, double radarRange, double divisionThreshold, double foodLimit, double maxSize, double age)
{
	this->maxSize = maxSize;
	this->aggresion = aggresion;
	this->radarRange = radarRange;
	this->divisionThreshold = divisionThreshold;
	this->foodLimit = foodLimit;
	this->maxSize = maxSize;
	this->maxAge = age;
}

void Genes::randomize()
{
	maxSize.randomize();
	aggresion.randomize();
	radarRange.randomize();
	divisionThreshold.randomize();
	foodLimit.randomize();
	maxSize.randomize();
	maxAge.randomize();
}