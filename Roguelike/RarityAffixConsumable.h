#pragma once
#include "RarityAffix.h"
#include "CreatureEffect.h"
#include <memory>

class RarityAffixConsumable : public RarityAffix
{
public:
	std::shared_ptr<CreatureEffect> effect;

	RarityAffixConsumable(std::string name, std::shared_ptr<CreatureEffect> effect) :
		RarityAffix(name, CONSUMABLE_AFFIX),
		effect(effect){}
};

