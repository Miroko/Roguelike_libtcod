#pragma once
#include "RarityAffixConsumable.h"
#include "EffectStaminaRegeneration.h"

class ConsumableAffixStaminaRegenerate : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription();

	ConsumableAffixStaminaRegenerate(std::string name, int duration, double percentage) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new EffectStaminaRegeneration(duration, percentage))){}
};

