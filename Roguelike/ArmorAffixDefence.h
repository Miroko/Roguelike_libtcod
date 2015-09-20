#pragma once
#include "RarityAffixArmor.h"

class ArmorAffixDefence : public RarityAffixArmor
{
private:
	double percentageValue;

public:
	double getDefenceModifier(){ return percentageValue; }
	std::string RarityAffixArmor::getDescription(GameObject &ownerObject);

	ArmorAffixDefence(std::string name, double percentageValue) :
		RarityAffixArmor(name),
		percentageValue(percentageValue){}
};

