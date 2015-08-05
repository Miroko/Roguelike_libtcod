#include "EffectHealth.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectHealth::getDescription(){
	return "Increases health by " + engine::string.multiplier(multiplier);
}

void EffectHealth::apply(Creature &creature){
	creature.healthMax = (int)(creature.healthMax * multiplier);
}

std::shared_ptr<CreatureEffect> EffectHealth::clone(){
	return std::shared_ptr<CreatureEffect>(new EffectHealth(*this));
}