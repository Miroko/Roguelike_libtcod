#pragma once
#include "Equipment.h"
#include "AliveObject.h"
#include <vector>
class EquipmentContainer
{
public:
	const std::vector<std::shared_ptr<Equipment>> allEquipment;

	void equipOn(std::shared_ptr<AliveObject> aliveObject) const;

	EquipmentContainer(const std::vector<std::shared_ptr<Equipment>> &allEquipment) : allEquipment(allEquipment){};
};

