#pragma once
#include "RarityAffix.h"

class CreatureSkill;
class RarityAffixAccessory : public RarityAffix
{
public:
	virtual double getMagicModifier(){ return 0.0; }
	virtual double getSpellPowerModifier(){ return 0.0; };
	virtual CreatureSkill* getSkill(){ return nullptr; }
	virtual double getProfiencyModifier(){ return 0.0; }

	RarityAffixAccessory(std::string name) : 
		RarityAffix(name, ACCESSORY_AFFIX){}
};

