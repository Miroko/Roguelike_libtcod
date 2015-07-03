#include "EffectHealth.h"
#include "Creature.h"

std::string EffectHealth::getDescription(){
	if (multiplier > 1)	return "Increased health";
	else return "Decreased health";
}

void EffectHealth::apply(Creature &creature){
	creature.setHealth((int)(creature.health * multiplier));
}