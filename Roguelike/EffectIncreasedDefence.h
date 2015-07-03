#pragma once
#include "ArmorEffect.h"

class EffectIncreasedDefence : public ArmorEffect
{
public:
	float multiplier;
	std::string getDescription();
	void apply(Armor &armor);

	EffectIncreasedDefence(float multiplier) :
		ArmorEffect(), multiplier(multiplier){}
};

