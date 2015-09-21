#include "CreatureEffectMagic.h"
#include "Creature.h"
#include "Engine.h"

std::string CreatureEffectMagic::getDescription(){
	return "Magic " + engine::string.value(engine::magicMax * modifier) + " for " + std::to_string(duration) + " turns";
}

void CreatureEffectMagic::apply(Creature &creature){
	creature.magicHit(-engine::magicMax * modifier);
	CreatureEffect::apply(creature);
}

int CreatureEffectMagic::getValue(){
	return (int)((engine::magicMax * modifier) * engine::valuePerMagic * duration);
}

std::shared_ptr<CreatureEffect> CreatureEffectMagic::clone(){
	return std::shared_ptr<CreatureEffect>(new CreatureEffectMagic(*this));
}