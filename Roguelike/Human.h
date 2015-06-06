#pragma once
#include "Race.h"
#include "Loot.h"
#include "Weapon.h"
#include "Creature.h"
#include <memory>
#include <vector>
namespace Race{
	namespace Human{
		class Human : public Race{
		public:		
			Human() : Race("Men"){};
		};

		class HumanBase : public Creature{
		public:
			HumanBase(std::string name, const RarityType &rarity, const Loot &loot) :
				Creature('h', name, MEDIUM, 10, TCODColor::lightAmber, rarity, loot){};
		};

		const Loot l = Loot(std::vector<Item>({ Sword() }));
		const HumanBase MAN_BASE = HumanBase("Man", Rarity::COMMON, l);
	}
}

