#include "WeaponAffixDamageIncrease.h"
#include "Engine.h"

std::string WeaponAffixDamageIncrease::getDescription(){
	return "Damage +" + engine::string.percentage(percentage);
}