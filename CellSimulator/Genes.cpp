#include "Genes.h"

Genes::Genes(): maxSpeed(0.1,2,0.1), aggresion(0, 100, 0), radarRange(0, 10, 0), divisionThreshold(0, 100, 0), foodLimit(0, 150, 0), maxSize(20, 50, 0), maxAge(1, 100, 1), type(0, 2, 0), metabolism(0.1, 2, 0.1)
{
	randomize();
}

Genes::Genes(double maxSpeed, double aggresion, double radarRange, double divisionThreshold, double foodLimit, double maxSize, double age, int type, double metabolism) : maxSpeed(0.1, 2, 0.1), aggresion(0, 100, 0), radarRange(0, 10, 0), divisionThreshold(0, 100, 0), foodLimit(0, 150, 0), maxSize(20, 50, 0), maxAge(1, 100, 1), type(0, 2, 0), metabolism(0.1, 2, 0.1)
{
	this->maxSpeed = maxSpeed;
	this->aggresion = aggresion;
	this->radarRange = radarRange;
	this->divisionThreshold = divisionThreshold;
	this->foodLimit = foodLimit;
	this->maxSize = maxSize;
	this->maxAge = age;
	this->type = type;
	this->metabolism = metabolism;
}

void Genes::randomize()
{
	maxSpeed.randomize();
	aggresion.randomize();
	radarRange.randomize();
	divisionThreshold.randomize();
	foodLimit.randomize();
	maxSize.randomize();
	maxAge.randomize();
	type.randomize();
	metabolism.randomize();
}

std::string Genes::toString()
{
	return "Max speed: " + std::to_string(this->maxSpeed.get()) + " aggresion: " + std::to_string(this->aggresion.get()) + " radar range: " + std::to_string(this->radarRange.get()) + " division threshold: " + std::to_string(this->divisionThreshold.get()) + " food limit: " + std::to_string(this->foodLimit.get()) + " max size: " + std::to_string(this->maxSize.get()) + " max age: " + std::to_string(this->maxAge.get()) + " type: " + std::to_string(this->type.get());
}
