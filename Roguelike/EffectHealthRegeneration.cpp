#include "EffectHealthRegeneration.h"
#include "Creature.h"


std::string EffectHealthRegeneration::getDescription(){
	if (amount > 0)	return "Regenerates health";
	else return "Degenerates health";
}

void EffectHealthRegeneration::apply(Creature &creature){
	creature.health += (int)(creature.healthMax * amount);
	if (creature.health > creature.healthMax) creature.health = creature.healthMax;
}