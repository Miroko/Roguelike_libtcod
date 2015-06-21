#pragma once
#include "Loot.h"
class LootContainer
{
public:
	const std::vector<std::shared_ptr<Loot>> allLoot;

	std::vector<std::shared_ptr<Item>> generateLoot() const;

	LootContainer(const std::vector<std::shared_ptr<Loot>> allLoot) : allLoot(allLoot){}
};

