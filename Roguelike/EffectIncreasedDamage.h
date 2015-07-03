#pragma once
#include "WeaponEffect.h"

class EffectIncreasedDamage : public WeaponEffect
{
public:
	float multiplier;
	std::string getDescription();
	void apply(Weapon &weapon);

	EffectIncreasedDamage(float multiplier) :
		WeaponEffect(), multiplier(multiplier){};
};

