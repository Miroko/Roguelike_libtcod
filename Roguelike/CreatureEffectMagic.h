#pragma once
#include "CreatureEffect.h"

class CreatureEffectMagic : public CreatureEffect
{
public:
	std::string CreatureEffect::getDescription();
	void CreatureEffect::apply(Creature &creature);
	int CreatureEffect::getValue();
	std::shared_ptr<CreatureEffect> CreatureEffect::clone();

	CreatureEffectMagic(std::string name, double modifier, double durationFromMax,
		std::shared_ptr<VisualEffect> visualEffectOnApply = nullptr) :
		CreatureEffect(name, modifier, durationFromMax, visualEffectOnApply){}
};

