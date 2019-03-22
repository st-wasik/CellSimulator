#pragma once

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

	double maxSpeed = 0;
	double aggresion = 0;
	double radarRange = 0;
	double divisionThreshold = 0;
	double foodLimit = 0;
	double maxSize = 0;
	double age = 0;
};