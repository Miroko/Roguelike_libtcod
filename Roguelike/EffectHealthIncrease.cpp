#include "EffectHealthIncrease.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectHealthIncrease::getDescription(){
	return "Increases health by " + engine::string.percentage(percentage);
}

void EffectHealthIncrease::apply(Creature &creature){
	creature.healthMax += (int)(creature.healthMax * percentage);
}

std::shared_ptr<CreatureEffect> EffectHealthIncrease::clone(){
	return std::shared_ptr<CreatureEffect>(new EffectHealthIncrease(*this));
}