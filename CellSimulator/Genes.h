#pragma once
#include "Ranged.h"
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
		double metabolism);

	Ranged<double, 0, 2> maxSpeed;
	Ranged<double, 0, 100> aggresion;
	Ranged<double, 0, 10> radarRange;
	Ranged<double, 0, 100> divisionThreshold;
	Ranged<double, 0, 150> foodLimit;
	Ranged<double, 20, 50> maxSize;
	Ranged<double, 1, 100> maxAge;
	Ranged<int, 0, 2> type;
	Ranged<double, 0, 2> metabolism;

	void randomize();
	std::string toString();
};
