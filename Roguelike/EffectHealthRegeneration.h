#pragma once
#include "CreatureEffect.h"

class EffectHealthRegeneration : public CreatureEffect
{
public:
	float amount;
	std::string getDescription();
	void apply(Creature &creature);

	EffectHealthRegeneration(float amount) : 
		CreatureEffect(),
		amount(amount){}
};

