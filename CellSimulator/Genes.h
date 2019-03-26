#pragma once
#include "Ranged.h"

struct Genes
{
	Genes();

	Genes(double maxSpeed, 
		double aggresion, 
		double radarRange, 
		double divisionThreshold,
		double foodLimit,
		double maxSize,
		double age);

	Ranged<double, 0, 2> maxSpeed{true};
	Ranged<double, 0, 100> aggresion{true};
	Ranged<double, 0, 10> radarRange{true};
	Ranged<double, 0, 100> divisionThreshold{true};
	Ranged<double, 0, 150> foodLimit{true};
	Ranged<double, 20, 50> maxSize{true};
	Ranged<double, 1, 100> age{true};
};