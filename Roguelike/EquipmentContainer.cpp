#include "EquipmentContainer.h"

void EquipmentContainer::equipOn(std::shared_ptr<AliveObject> aliveObject) const{
	for (auto &equipment : allEquipment){
		aliveObject->equip(equipment);
	}
}