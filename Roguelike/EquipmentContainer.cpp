#include "EquipmentContainer.h"

void EquipmentContainer::equipOn(AliveObject &aliveObject){
	for (auto &equipment : allEquipment){
		aliveObject.equipItem(*equipment);
	}
}