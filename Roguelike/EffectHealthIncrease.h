#pragma once
#include "CreatureEffect.h"

class EffectHealthIncrease : public CreatureEffect
{
public:
	float percentage;
	std::string getDescription();
	void apply(Creature &creature);
	std::shared_ptr<CreatureEffect> clone();

	EffectHealthIncrease(float percentage) :
		CreatureEffect(1),
		percentage(percentage){};
};

