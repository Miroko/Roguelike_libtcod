#pragma once
#include "ItemContainer.h"
#include "Equipment.h"
#include "Consumable.h"

class PlayerInventory
{
public:
	const float MAX_WEIGHT = 50;
	int currency;

	ItemContainer temporary; //For gui

	float getCurrentWeight();

	void equip(std::shared_ptr<Equipment> item);
	void unequip(std::shared_ptr<Equipment> item);
	void consume(std::shared_ptr<Consumable> item);
	void drop(std::shared_ptr<Item> item);

	PlayerInventory(){};
};

