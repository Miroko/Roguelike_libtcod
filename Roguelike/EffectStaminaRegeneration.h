#pragma once
#include "CreatureEffect.h"

class EffectStaminaRegeneration : public CreatureEffect
{
public:
	double percentage;
	std::string CreatureEffect::getDescription();
	void CreatureEffect::apply(Creature &creature);
	int CreatureEffect::getValue();
	std::shared_ptr<CreatureEffect> CreatureEffect::clone();

	EffectStaminaRegeneration(int duration, double percentage) :
		CreatureEffect(duration),
		percentage(percentage){}
};

