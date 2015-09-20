#include "AccessoryAffixMagic.h"
#include "Accessory.h"
#include "Engine.h"

std::string AccessoryAffixMagic::getDescription(GameObject &ownerObject){
	Accessory &ownerAccessory = static_cast<Accessory&>(ownerObject);
	return "Magic: " + engine::string.value(engine::magicMax * getMagicModifier() * ownerAccessory.getSpellPowerBase());
}