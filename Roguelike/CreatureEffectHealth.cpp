#include "CreatureEffectHealth.h"
#include "Creature.h"
#include "Engine.h"

int CreatureEffectHealth::getEffectAmountLeft(){
	return engine::healthMax * modifier * duration;
}

std::string CreatureEffectHealth::getDescription(){
	return "Health " + engine::string.value(getEffectAmountLeft()) + " in " + std::to_string(duration) + " turns";
}

void CreatureEffectHealth::apply(Creature &creature){
	creature.healthHit(-getEffectAmountLeft() / duration);
	CreatureEffect::apply(creature);
}

int CreatureEffectHealth::getValue(){
	return (int)(getEffectAmountLeft() * engine::valuePerHealth);
}

std::shared_ptr<CreatureEffect> CreatureEffectHealth::clone(){
	return std::shared_ptr<CreatureEffect>(new CreatureEffectHealth(*this));
}