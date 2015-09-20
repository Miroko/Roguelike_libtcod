#include "AccessoryAffixSpellPower.h"
#include "Accessory.h"
#include "Engine.h"

std::string AccessoryAffixSpellPower::getDescription(GameObject &ownerObject){
	Accessory &ownerAccessory = static_cast<Accessory&>(ownerObject);
	return "Spell power " + engine::string.percentageValue(ownerAccessory.getSpellPowerBase() * getSpellPowerModifier());
}
