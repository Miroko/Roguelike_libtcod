#pragma once
#include "ArmorEffect.h"
#include <memory>

class Armor;
class RarityModArmor
{
public:
	std::shared_ptr<ArmorEffect> effect;

	void apply(Armor &armor);

	RarityModArmor(std::shared_ptr<ArmorEffect> effect) : effect(effect){};
};

