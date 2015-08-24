#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixStamina : public RarityAffixWeapon
{
public:	
	double percentage;
	double getStaminaModifier(){ return percentage; }
	std::string RarityAffixWeapon::getDescription();

	WeaponAffixStamina(std::string name, double percentage) :
		RarityAffixWeapon(name),
		percentage(percentage){}
};

