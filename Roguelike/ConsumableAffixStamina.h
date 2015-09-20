#pragma once
#include "RarityAffixConsumable.h"
#include "CreatureEffectStamina.h"

class ConsumableAffixStamina : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription(GameObject &ownerObject);

	ConsumableAffixStamina(std::string name, double modifier, double durationFromMax) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new CreatureEffectStamina(name, modifier, durationFromMax))){}
};
