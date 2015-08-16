#pragma once
#include "RarityAffix.h"

class RarityAffixArmor : public RarityAffix
{
public:
	virtual double getDefenceMultiplier(){ return 0.0f; }

	RarityAffixArmor(std::string name) :
		RarityAffix(name){};
};

