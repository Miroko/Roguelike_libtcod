#pragma once
#include "RarityAffixConsumable.h"
#include "CreatureEffectHealth.h"

class ConsumableAffixHealth : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription(GameObject &ownerObject);

	ConsumableAffixHealth(std::string name, double modifier, double durationFromMax) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new CreatureEffectHealth(name, modifier, durationFromMax))){}
};

