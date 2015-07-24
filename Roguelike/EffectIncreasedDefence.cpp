#include "EffectIncreasedDefence.h"
#include "Armor.h"
#include "Engine.h"

std::string EffectIncreasedDefence::getDescription(){
	return "Defence " + engine::string.multiplier(multiplier);
}
void EffectIncreasedDefence::apply(Armor &armor){
	armor.defence = (int)(armor.defence * multiplier);
}