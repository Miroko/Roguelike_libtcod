#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixAccuracy : public RarityAffixWeapon
{
public:
	double percentage;
	double getAccuracyModifier(){ return percentage; }
	std::string RarityAffixWeapon::getDescription();

	WeaponAffixAccuracy(std::string name, double percentage) :
		RarityAffixWeapon(name),
		percentage(percentage){}
};

