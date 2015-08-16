#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixDamageIncrease : public RarityAffixWeapon
{
public:
	double percentage;
	double getDamageMultiplier(){ return 1.0f + percentage; }
	std::string RarityAffixWeapon::getDescription();

	WeaponAffixDamageIncrease(std::string name, double percentage) :
		RarityAffixWeapon(name),
		percentage(percentage){}
};

