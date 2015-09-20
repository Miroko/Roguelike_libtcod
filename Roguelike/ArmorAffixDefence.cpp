#include "ArmorAffixDefence.h"
#include "Armor.h"
#include "Engine.h"

std::string ArmorAffixDefence::getDescription(GameObject &ownerObject){
	Armor &ownerArmor = static_cast<Armor&>(ownerObject);
	return "Defence " + engine::string.value(ownerArmor.getDefenceBase() * getDefenceModifier());
}