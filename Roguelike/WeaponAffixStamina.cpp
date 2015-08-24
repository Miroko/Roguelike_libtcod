#include "WeaponAffixStamina.h"
#include "Engine.h"

std::string WeaponAffixStamina::getDescription(){
	return "Stamina cost of actions " + engine::string.percentage(percentage);
}
