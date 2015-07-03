#pragma once
#include "CreatureEffect.h"

class EffectHealth : public CreatureEffect
{
public:
	float multiplier;
	std::string getDescription();
	void apply(Creature &creature);

	EffectHealth(float multiplier) :
		CreatureEffect(), multiplier(multiplier){};
};

