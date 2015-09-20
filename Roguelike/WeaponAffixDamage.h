#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixDamage : public RarityAffixWeapon
{
private:
	double percentageValue;

public:
	double getDamageModifier(){ return percentageValue; }
	std::string RarityAffixWeapon::getDescription(GameObject &ownerObject);

	WeaponAffixDamage(std::string name, double percentageValue) :
		RarityAffixWeapon(name),
		percentageValue(percentageValue){}
};

