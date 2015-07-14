#pragma once
#include "CreatureEffect.h"

class EffectHealthRegeneration : public CreatureEffect
{
public:
	int amount;
	std::string getDescription();
	void apply(Creature &creature);

	EffectHealthRegeneration(int amount) : CreatureEffect(), amount(amount){}
};

