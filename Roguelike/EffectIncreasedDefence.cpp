#include "EffectIncreasedDefence.h"
#include "Armor.h"

std::string EffectIncreasedDefence::getDescription(){
	if (multiplier > 1) return "Increased defence";
	else return "Decreased defence";
}
void EffectIncreasedDefence::apply(Armor &armor){
	armor.defence = (int)(armor.defence * multiplier);
}