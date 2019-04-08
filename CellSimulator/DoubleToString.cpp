#include "DoubleToString.h"

std::string doubleToString(double value, std::streamsize precision)
{
	std::ostringstream stream;
	stream << std::setprecision(precision);
	stream << std::fixed;
	stream << value;
	return stream.str();
}