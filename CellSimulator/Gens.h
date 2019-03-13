#pragma once
class Gens
{
public:
	Gens();
	~Gens();
	enum class GensType	{maxSpeed, aggresion, radarRange, divisionThreshold, foodLimit, maxSize, age};
	double& operator [] (GensType genstype);
private:
	double maxSpeed, aggresion, radarRange, divisionThreshold, foodLimit, maxSize, age, _default;
};

