#pragma once
#include "Weapon.h"
#include <vector>
class Loot
{
public:
	std::vector<Item> items;

	Loot(std::vector<Item> items) : items(items){};
};

