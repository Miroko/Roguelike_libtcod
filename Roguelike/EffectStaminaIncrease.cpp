#include "EffectStaminaIncrease.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectStaminaIncrease::getDescription(){
	return "Increases stamina by " + engine::string.percentage(percentage);
}

void EffectStaminaIncrease::apply(Creature &creature){
	creature.staminaMax += (int)(creature.staminaMax * percentage);
}

std::shared_ptr<CreatureEffect> EffectStaminaIncrease::clone(){
	return std::shared_ptr<CreatureEffect>(new EffectStaminaIncrease(*this));
}
