#include "CreatureEffectStamina.h"
#include "Creature.h"
#include "Engine.h"

int CreatureEffectStamina::getEffectAmountLeft(){
	return engine::staminaMax * modifier * duration;
}

std::string CreatureEffectStamina::getDescription(){
	return "Stamina " + engine::string.value(getEffectAmountLeft()) + " in " + std::to_string(duration) + " turns";
}

void CreatureEffectStamina::apply(Creature &creature){
	creature.staminaHit(-getEffectAmountLeft() / duration);
	CreatureEffect::apply(creature);
}

int CreatureEffectStamina::getValue(){
	return (int)(getEffectAmountLeft() * engine::valuePerStamina);
}

std::shared_ptr<CreatureEffect> CreatureEffectStamina::clone(){
	return std::shared_ptr<CreatureEffect>(new CreatureEffectStamina(*this));
}