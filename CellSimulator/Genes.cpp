#include "Genes.h"
#include "DoubleToString.h"

Genes::Genes(): maxSpeed(0.1,2,0.1), aggresion(0, 100, 0), radarRange(0, 500, 0), divisionThreshold(0, 100, 0), foodLimit(50, 150, 0), maxSize(20, 50, 0), maxAge(1, 100, 1), type(-1, 2, 0), metabolism(0.1, 2, 0.1),turningRate(0.5, 7, 4)
{
	randomize();
}

Genes::Genes(double maxSpeed, double aggresion, double radarRange, double divisionThreshold, double foodLimit, double maxSize, double age, int type, double metabolism, double turningRate) : maxSpeed(0.1, 2, maxSpeed), aggresion(0, 100, aggresion), radarRange(0, 500, radarRange), divisionThreshold(0, 100, divisionThreshold), foodLimit(50, 150, foodLimit), maxSize(20, 50, maxSize), maxAge(1, 100, age), type(-1, 2, type), metabolism(0.1, 2, metabolism), turningRate(0.5, 7, turningRate)
{
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
	type = randomInt(0, type.getMax()); //-1 for special
	metabolism.randomize();
	turningRate.randomize();
}

std::string Genes::toString()
{
	return "Max speed: " + doubleToString(this->maxSpeed.get(),2) +
		" aggresion: " + doubleToString(this->aggresion.get(),2) +
		" radar range: " + doubleToString(this->radarRange.get(),2) +
		" division threshold: " + doubleToString(this->divisionThreshold.get(),2) +
		" food limit: " + doubleToString(this->foodLimit.get(),2) +
		" max size: " + doubleToString(this->maxSize.get(),2) +
		" max age: " + doubleToString(this->maxAge.get(),2) +
		" type: " + doubleToString(this->type.get(),2) +
		" metabolism: " + doubleToString(this->metabolism.get(),2) +
		" turning rate: " + doubleToString(this->turningRate.get(),2);
}
