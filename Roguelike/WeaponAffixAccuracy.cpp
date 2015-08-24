#include "WeaponAffixAccuracy.h"
#include "Engine.h"

std::string WeaponAffixAccuracy::getDescription(){
	return "Accuracy " + engine::string.percentage(percentage);
}