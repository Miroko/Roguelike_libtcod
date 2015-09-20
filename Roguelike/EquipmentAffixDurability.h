#pragma once
#include "RarityAffixEquipment.h"

class EquipmentAffixDurability : public RarityAffixEquipment
{
private:
	double percentageValue;

public:
	double getDurabilityModifier(){ return percentageValue; }
	std::string RarityAffix::getDescription(GameObject &ownerObject);

	EquipmentAffixDurability(std::string name, double percentageValue) :
		RarityAffixEquipment(name),
		percentageValue(percentageValue){}
};

