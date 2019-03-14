#pragma once
class Genes
{
public:
	Genes();
	~Genes();
	enum class GeneType	{maxSpeed, aggresion, radarRange, divisionThreshold, foodLimit, maxSize, age};
	double& operator [] (GeneType GeneType);
private:
	double maxSpeed, aggresion, radarRange, divisionThreshold, foodLimit, maxSize, age, _default;
};

