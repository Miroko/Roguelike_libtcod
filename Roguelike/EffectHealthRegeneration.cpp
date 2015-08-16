#include "EffectHealthRegeneration.h"
#include "Creature.h"
#include "Engine.h"

std::string EffectHealthRegeneration::getDescription(){
	return "Regenerate " + engine::string.percentage(percentage) + " health for " + std::to_string(duration) + " turns";
}

void EffectHealthRegeneration::apply(Creature &creature){
	creature.healthCurrent += (int)(creature.healthMax * percentage);
	if (creature.healthCurrent > creature.healthMax) creature.healthCurrent = creature.healthMax;
}

int EffectHealthRegeneration::getValue(){
	return (int)((engine::healthMax * percentage) * engine::valuePerHealth * duration);
}

std::shared_ptr<CreatureEffect> EffectHealthRegeneration::clone(){
	return std::shared_ptr<CreatureEffect>(new EffectHealthRegeneration(*this));
}