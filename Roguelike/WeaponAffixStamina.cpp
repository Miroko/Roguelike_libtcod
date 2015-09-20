#include "WeaponAffixStamina.h"
#include "Engine.h"

std::string WeaponAffixStamina::getDescription(GameObject &ownerObject){
	return "Stamina cost " + engine::string.percentageValue(percentageValue);
}
