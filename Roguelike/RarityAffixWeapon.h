#pragma once
#include "RarityAffix.h"

class RarityAffixWeapon : public RarityAffix
{
public:
	virtual double getDamageMultiplier(){ return 1.0f; }

	RarityAffixWeapon(std::string name) :
		RarityAffix(name){};
};

