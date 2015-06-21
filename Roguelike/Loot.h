#pragma once
#include "Item.h"
#include <vector>
#include <memory>
class Loot
{
public:
	float dropChance;
	const std::shared_ptr<Item> item;

	Loot(const std::shared_ptr<Item> &item, float dropChance) : item(item), dropChance(dropChance){};
};

