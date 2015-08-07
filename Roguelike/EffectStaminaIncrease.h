#pragma once
#include "CreatureEffect.h"

class EffectStaminaIncrease : public CreatureEffect
{
public:
	float percentage;
	std::string getDescription();
	void apply(Creature &creature);
	std::shared_ptr<CreatureEffect> clone();

	EffectStaminaIncrease(float percentage) :
		CreatureEffect(1),
		percentage(percentage){};
};

