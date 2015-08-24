#pragma once
#include "RarityAffix.h"

class RarityAffixArmor : public RarityAffix
{
public:
	virtual double getDefenceModifier(){ return 0.0; }

	RarityAffixArmor(std::string name) :
		RarityAffix(name, ARMOR_AFFIX){};
};

