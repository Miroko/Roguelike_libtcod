#pragma once
#include "Loot.h"
#include "Creature.h"
#include <memory>
#include <vector>

class Human : public Creature{
	public:		
		Human(std::string name, const TCODColor color, int health, const RarityType &rarity, const Loot &loot) :Creature('h', name, MEDIUM, health, color, rarity, loot){};
	};

const Loot MAN_LOOT = Loot(std::vector<std::shared_ptr<Weapon>>({ SWORD }));
const Human MAN = Human("Man", TCODColor::lightestAmber, 30, COMMON, MAN_LOOT);