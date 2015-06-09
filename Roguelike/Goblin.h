#pragma once
#include "Race.h"
#include "Creature.h"

class Goblin : public Race{
public:
	Goblin() : Race("Goblins"){};
};

const Loot GOBLIN_LOOT = Loot(std::vector<Weapon>({ DAGGER }));
const Creature GOBLIN = Creature('g', "Goblin", DynamicObject::MEDIUM, 10, TCODColor::lightChartreuse, COMMON, GOBLIN_LOOT);