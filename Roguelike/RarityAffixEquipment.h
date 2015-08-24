#pragma once
#include "RarityAffix.h"

class RarityAffixEquipment : public RarityAffix
{
public:
	virtual double getDurabilityModifier(){ return 0.0; }

	RarityAffixEquipment(std::string name) :
		RarityAffix(name, EQUIPMENT_AFFIX){}
};

