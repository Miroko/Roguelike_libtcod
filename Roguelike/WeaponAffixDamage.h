#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixDamage : public RarityAffixWeapon
{
public:
	double percentage;
	double getDamageModifier(){ return percentage; }
	std::string RarityAffixWeapon::getDescription();

	WeaponAffixDamage(std::string name, double percentage) :
		RarityAffixWeapon(name),
		percentage(percentage){}
};

