#pragma once
#include "CreatureEffect.h"

class EffectHealth : public CreatureEffect
{
public:
	float multiplier;
	std::string getDescription();
	void apply(Creature &creature);
	std::shared_ptr<CreatureEffect> clone();

	EffectHealth(float multiplier) :
		CreatureEffect(1),
		multiplier(multiplier){};
};

