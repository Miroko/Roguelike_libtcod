#include "EffectIncreasedDamage.h"
#include "Weapon.h"
#include "Engine.h"

std::string EffectIncreasedDamage::getDescription(){
	return "Damage " + engine::string.multiplier(multiplier);
}

void EffectIncreasedDamage::apply(Weapon &weapon){
	weapon.damage = (int)(weapon.damage * multiplier);
}