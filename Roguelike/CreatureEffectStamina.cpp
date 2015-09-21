#include "CreatureEffectStamina.h"
#include "Creature.h"
#include "Engine.h"

std::string CreatureEffectStamina::getDescription(){
	return "Stamina " + engine::string.value(engine::staminaMax * modifier) + " for " + std::to_string(duration) + " turns";
}

void CreatureEffectStamina::apply(Creature &creature){
	creature.staminaHit(-engine::staminaMax * modifier);
	CreatureEffect::apply(creature);
}

int CreatureEffectStamina::getValue(){
	return (int)((engine::staminaMax * modifier) * engine::valuePerStamina * duration);
}

std::shared_ptr<CreatureEffect> CreatureEffectStamina::clone(){
	return std::shared_ptr<CreatureEffect>(new CreatureEffectStamina(*this));
}