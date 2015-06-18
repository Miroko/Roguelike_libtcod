#pragma once
#include "Creature.h"

class Goblin : public Creature{
public:
	Goblin(std::string name, const TCODColor color, int health, const RarityType &rarity, const Loot &loot) : Creature('g', name, MEDIUM, health, color, rarity, loot){};
};

const Loot GOBLIN_LOOT = Loot(std::vector<std::shared_ptr<Weapon>>({ DAGGER }));
const Goblin GOBLIN = Goblin("Goblin", TCODColor::lightChartreuse, 10, COMMON, GOBLIN_LOOT);