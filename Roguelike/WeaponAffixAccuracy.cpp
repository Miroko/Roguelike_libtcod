#include "WeaponAffixAccuracy.h"
#include "Engine.h"

std::string WeaponAffixAccuracy::getDescription(GameObject &ownerObject){
	return "Accuracy " + engine::string.percentageValue(getAccuracyModifier());
}