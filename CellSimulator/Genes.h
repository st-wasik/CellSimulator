#pragma once
#include "DynamicRanged.h"
#include <string>
#include <iostream>


struct Genes
{
	Genes();

	Genes(double maxSpeed, 
		double aggresion, 
		double radarRange, 
		double divisionThreshold,
		double foodLimit,
		double maxSize,
		double age,
		int type,
		double metabolism,
		double turningRate);

	
	DynamicRanged<double> maxSpeed; //<0.1, 2>
	DynamicRanged<double> aggresion; //<0, 100>;
	DynamicRanged<double> radarRange; //<0, 500>
	DynamicRanged<double> divisionThreshold; //<0, 100>
	DynamicRanged<double> foodLimit; //<0, 150>
	DynamicRanged<double> maxSize; //<20, 50>
	DynamicRanged<double> maxAge; //<1, 100>
	DynamicRanged<int> type; //<-1, 2> -1 = Special (Pizza/Lettuce), 0 = Omnivore, 1 = Herbivore, 2 = Carnivore
	DynamicRanged<double> metabolism;//<0.1, 2>
	DynamicRanged<double> turningRate;//<0.5,7>

	void randomize();
	std::string toString();
};
