#pragma once
#include "Race.h"
#include "Creature.h"

namespace race{
	namespace goblin{
		class Goblin : public Race{
		public:
			Goblin() : Race("Goblins"){};
		};

		class GoblinBase : public Creature{
		public:
			GoblinBase(std::string name, const RarityType &rarity, const Loot &loot) :
				Creature('g', name, MEDIUM, 10, TCODColor::lightChartreuse, rarity, loot){};
		};

		const Loot l = Loot(std::vector<Item>({ Sword() }));
		const GoblinBase GOBLIN_BASE = GoblinBase("Goblin", Rarity::COMMON, l);
	}
}

