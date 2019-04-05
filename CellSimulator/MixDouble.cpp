#include "MixDouble.h"

double MixDouble(double a, double b)
{
	union LongDouble
	{
		double d;
		unsigned long long ull;
	};
	LongDouble convA,convB,fin;
	convA.d = a;
	convB.d = b;
	std::bitset<64> bitsA = convA.ull, bitsB = convB.ull, bitsFin;

	for (unsigned i = 0; i < 64; ++i)
	{
		if (i % 2 == 0)
		{
			bitsFin[i] = bitsA[i];
		}
		else
		{
			bitsFin[i] = bitsB[i];
		}
	}
	fin.ull = bitsFin.to_ullong();
	return fin.d;
}
