#pragma once
#include "RarityAffixConsumable.h"
#include "EffectHealthRegeneration.h"

class ConsumableAffixHealthRegenerate : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription();

	ConsumableAffixHealthRegenerate(std::string name, int duration, double percentage) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new EffectHealthRegeneration(duration, percentage))){}
};

