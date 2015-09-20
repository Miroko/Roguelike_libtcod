#include "EquipmentAffixDurability.h"
#include "Equipment.h"
#include "Engine.h"

std::string EquipmentAffixDurability::getDescription(GameObject &ownerObject){
	Equipment &ownerEquipment = static_cast<Equipment&>(ownerObject);
	return "Durability " + engine::string.value(ownerEquipment.getDurabilityMaxBase() * getDurabilityModifier());
}

