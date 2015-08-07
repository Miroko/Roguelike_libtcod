#pragma once
#include "CreatureEffect.h"

class EffectStaminaRegeneration : public CreatureEffect
{
public:
	float percentage;
	std::string getDescription();
	void apply(Creature &creature);
	std::shared_ptr<CreatureEffect> clone();

	EffectStaminaRegeneration(int duration, float percentage) :
		CreatureEffect(duration),
		percentage(percentage){}
};

