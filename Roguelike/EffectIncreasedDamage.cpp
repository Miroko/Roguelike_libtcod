#include "EffectIncreasedDamage.h"
#include "Weapon.h"

std::string EffectIncreasedDamage::getDescription(){
	if (multiplier > 1) return "Increased damage";
	else return "Decreased damage";
}

void EffectIncreasedDamage::apply(Weapon &weapon){
	weapon.damage = (int)(weapon.damage * multiplier);
}