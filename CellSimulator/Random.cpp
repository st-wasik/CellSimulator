#include"Random.h"

int randomInt(int a, int b)
{
	if (a > b)
	{
		std::swap(a, b);
	}
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);

	return dis(gen);
}

double randomReal(double a, double b)
{
	if (a > b)
	{
		std::swap(a, b);
	}
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);

	return dis(gen);
}
