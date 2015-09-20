#pragma once
#include "RarityAffixWeapon.h"

class WeaponAffixAccuracy : public RarityAffixWeapon
{
private:
	double percentageValue;

public:
	double getAccuracyModifier(){ return percentageValue; }
	std::string RarityAffixWeapon::getDescription(GameObject &ownerObject);

	WeaponAffixAccuracy(std::string name, double percentageValue) :
		RarityAffixWeapon(name),
		percentageValue(percentageValue){}
};

