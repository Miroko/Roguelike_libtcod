#include "String.h"

std::string String::weight(float weight, int precision){
	int rounded = (int)weight;
	int decimals = pow(10, precision);
	int decimalPart = weight * decimals - rounded * decimals;
	return std::to_string(rounded) + "." + std::to_string(decimalPart);
}