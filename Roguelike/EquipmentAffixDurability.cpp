#include "EquipmentAffixDurability.h"
#include "Engine.h"

std::string EquipmentAffixDurability::getDescription(){
	return "Durability " + engine::string.percentage(percentage);
}

