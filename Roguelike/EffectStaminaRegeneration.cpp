#include "EffectStaminaRegeneration.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectStaminaRegeneration::getDescription(){
	return "Regenerates " + engine::string.percentage(percentage) + " stamina for " + std::to_string(duration) + " turns";
}

void EffectStaminaRegeneration::apply(Creature &creature){
	creature.staminaCurrent += (int)(creature.staminaMax * percentage);
	if (creature.staminaCurrent > creature.staminaMax) creature.staminaCurrent = creature.staminaMax;
}

std::shared_ptr<CreatureEffect> EffectStaminaRegeneration::clone(){
	return std::shared_ptr<CreatureEffect>(new EffectStaminaRegeneration(*this));
}