#include"Random.h"

int RandomInt(int a, int b)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);

	return dis(gen);
}

double RandomReal(double a, double b)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);

	return dis(gen);
}
