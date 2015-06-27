#pragma once
#include "Item.h"

class Loot
{
public:
	float dropChance;
	Item *item;

	Loot(Item &item, float dropChance) : item(&item), dropChance(dropChance){};
	Loot(){};
};

