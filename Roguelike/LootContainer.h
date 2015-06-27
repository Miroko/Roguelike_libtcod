#pragma once
#include "Loot.h"
#include <vector>
#include <memory>

class LootContainer
{
public:
	std::vector<Loot> containerLoot;

	std::vector<std::shared_ptr<Item>> generateLoot();

	LootContainer(std::vector<Loot> containerLoot) : containerLoot(containerLoot){}
};

