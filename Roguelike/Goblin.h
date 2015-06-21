#pragma once
#include "Creature.h"

class Goblin : public Creature{
public:
	Goblin(std::string name, const TCODColor color, int health, const RarityType &rarity, const LootContainer &loot) :
		Creature('g', name, MEDIUM, health, color, rarity, loot){};
};

const LootContainer GOBLIN_LOOT = LootContainer(std::vector<std::shared_ptr<Loot>>({
	std::shared_ptr<Loot>(new Loot(DAGGER, 0.2)),
	std::shared_ptr<Loot>(new Loot(HEALTH_POTION, 0.2))
}));
const EquipmentContainer GOBLIN_EQUIPMENT = EquipmentContainer(std::vector<std::shared_ptr<Equipment>>({
	DAGGER,
	LEATHER_BODY
}));
const Goblin GOBLIN = Goblin("Goblin", TCODColor::lightChartreuse, 10, RARITY_COMMON, GOBLIN_LOOT);