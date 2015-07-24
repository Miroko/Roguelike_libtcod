#include "EffectHealth.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectHealth::getDescription(){
	return "Health " + engine::string.multiplier(multiplier);
}

void EffectHealth::apply(Creature &creature){
	creature.setHealth((int)(creature.health * multiplier));
}