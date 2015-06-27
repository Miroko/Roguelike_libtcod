#pragma once
#include "Equipment.h"
#include "AliveObject.h"
#include <vector>
class EquipmentContainer
{
public:
	std::vector<Equipment*> allEquipment;

	void equipOn(AliveObject &aliveObject);

	EquipmentContainer(std::vector<Equipment*> &allEquipment) : allEquipment(allEquipment){};
};

