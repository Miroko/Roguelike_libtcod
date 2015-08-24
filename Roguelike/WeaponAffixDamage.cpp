#include "WeaponAffixDamage.h"
#include "Engine.h"

std::string WeaponAffixDamage::getDescription(){
	return "Damage " + engine::string.percentage(percentage);
}