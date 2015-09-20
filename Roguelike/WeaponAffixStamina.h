#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixStamina : public RarityAffixWeapon
{
private:
	double percentageValue;

public:	
	double getStaminaModifier(){ return percentageValue; }
	std::string RarityAffixWeapon::getDescription(GameObject &ownerObject);

	WeaponAffixStamina(std::string name, double percentageValue) :
		RarityAffixWeapon(name),
		percentageValue(percentageValue){}
};

