#include "EffectHealthRegeneration.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectHealthRegeneration::getDescription(){
	return "Regenerates " + engine::string.percentage(amount) + " health for " + std::to_string(duration) + " turns";
}

void EffectHealthRegeneration::apply(Creature &creature){
	creature.health += (int)(creature.healthMax * amount);
	if (creature.health > creature.healthMax) creature.health = creature.healthMax;
}

std::shared_ptr<CreatureEffect> EffectHealthRegeneration::clone(){
	return std::shared_ptr<CreatureEffect>(new EffectHealthRegeneration(*this));
}