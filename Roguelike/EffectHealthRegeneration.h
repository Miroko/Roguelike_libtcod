#pragma once
#include "CreatureEffect.h"

class EffectHealthRegeneration : public CreatureEffect
{
public:
	float percentage;
	std::string getDescription();
	void apply(Creature &creature);
	std::shared_ptr<CreatureEffect> clone();

	EffectHealthRegeneration(int duration, float percentage) :
		CreatureEffect(duration),
		percentage(percentage){}
};

