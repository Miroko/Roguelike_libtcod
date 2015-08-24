#pragma once
#include "RarityAffixEquipment.h"

class EquipmentAffixDurability : public RarityAffixEquipment
{
public:
	double percentage;
	double getDurabilityModifier(){ return percentage; }
	std::string RarityAffix::getDescription();

	EquipmentAffixDurability(std::string name, double percentage) :
		RarityAffixEquipment(name),
		percentage(percentage){}
};

