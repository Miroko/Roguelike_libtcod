#pragma once
#include "CreatureEffect.h"

class EffectHealthRegeneration : public CreatureEffect
{
public:
	double percentage;
	std::string CreatureEffect::getDescription();
	void CreatureEffect::apply(Creature &creature);
	int CreatureEffect::getValue();
	std::shared_ptr<CreatureEffect> CreatureEffect::clone();

	EffectHealthRegeneration(int duration, double percentage) :
		CreatureEffect(duration),
		percentage(percentage){}
};

