#pragma once
#include "RarityAffixArmor.h"

class ArmorAffixDefence : public RarityAffixArmor
{
public:
	double percentage;
	double getDefenceModifier(){ return percentage; }
	std::string RarityAffixArmor::getDescription();

	ArmorAffixDefence(std::string name, double percentage) :
		RarityAffixArmor(name),
		percentage(percentage){}
};

