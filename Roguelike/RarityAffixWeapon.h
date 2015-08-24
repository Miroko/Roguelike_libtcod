#pragma once
#include "RarityAffix.h"

class RarityAffixWeapon : public RarityAffix
{
public:
	virtual double getDamageModifier(){ return 0.0; }
	virtual double getAccuracyModifier(){ return 0.0; }
	virtual double getStaminaModifier(){ return 0.0; }

	RarityAffixWeapon(std::string name) :
		RarityAffix(name, WEAPON_AFFIX){};
};

