#pragma once
#include <string>

class Armor;
class ArmorEffect
{
public:
	virtual std::string getDescription() = 0;
	virtual void apply(Armor &armor) = 0;

	ArmorEffect(){}
};

