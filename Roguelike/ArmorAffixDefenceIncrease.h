#pragma once
#include "RarityAffixArmor.h"

class ArmorAffixDefenceIncrease : public RarityAffixArmor
{
public:
	double percentage;
	double getDefenceMultiplier(){ return percentage; }
	std::string RarityAffixArmor::getDescription();

	ArmorAffixDefenceIncrease(std::string name, double percentage) :
		RarityAffixArmor(name),
		percentage(percentage){}
};

