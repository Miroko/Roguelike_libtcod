#include "CreatureEffectMagic.h"
#include "Creature.h"
#include "Engine.h"

int CreatureEffectMagic::getEffectAmountLeft(){
	return engine::magicMax * modifier * duration;
}

std::string CreatureEffectMagic::getDescription(){
	return "Magic " + engine::string.value(getEffectAmountLeft()) + " in " + std::to_string(duration) + " turns";
}

void CreatureEffectMagic::apply(Creature &creature){
	creature.magicHit(-getEffectAmountLeft() / duration);
	CreatureEffect::apply(creature);
}

int CreatureEffectMagic::getValue(){
	return (int)(getEffectAmountLeft() * engine::valuePerMagic);
}

std::shared_ptr<CreatureEffect> CreatureEffectMagic::clone(){
	return std::shared_ptr<CreatureEffect>(new CreatureEffectMagic(*this));
}