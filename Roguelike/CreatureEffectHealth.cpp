#include "CreatureEffectHealth.h"
#include "Creature.h"
#include "Engine.h"

std::string CreatureEffectHealth::getDescription(){
	return "Health " + engine::string.value(engine::healthMax * modifier) + " for " + std::to_string(duration) + " turns";
}

void CreatureEffectHealth::apply(Creature &creature){
	creature.healthHit(-engine::healthMax * modifier);
	CreatureEffect::apply(creature);
}

int CreatureEffectHealth::getValue(){
	return (int)((engine::healthMax * modifier) * engine::valuePerHealth * duration);
}

std::shared_ptr<CreatureEffect> CreatureEffectHealth::clone(){
	return std::shared_ptr<CreatureEffect>(new CreatureEffectHealth(*this));
}