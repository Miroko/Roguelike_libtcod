#pragma once
#include "Equipment.h"

class Armor : public Equipment
{
public:
	int defence;

	std::string getStatistics();
	int getValue();

	Armor(std::string name, Glyph glyph, float weight, int defence, Type type) :
		Equipment(name, glyph, weight, type),
		defence(defence){};
};
