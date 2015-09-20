#pragma once
#include "CreatureEffect.h"

class CreatureEffectHealth : public CreatureEffect
{
public:
	std::string CreatureEffect::getDescription();
	void CreatureEffect::apply(Creature &creature);
	int CreatureEffect::getValue();
	std::shared_ptr<CreatureEffect> CreatureEffect::clone();

	CreatureEffectHealth(std::string name, double modifier, double durationFromMax) :
		CreatureEffect(name, modifier, durationFromMax){}
};

