#pragma once
#include "CreatureEffect.h"
#include <memory>

class Creature;
class RarityModCreature
{
public:
	std::shared_ptr<CreatureEffect> effect;

	void apply(Creature &creature);

	RarityModCreature(std::shared_ptr<CreatureEffect> effect) : effect(effect){};
};

