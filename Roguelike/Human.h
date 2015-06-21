#pragma once
#include "Creature.h"

class Human : public Creature{
	public:		
		Human(std::string name, const TCODColor color, int health, const RarityType &rarity, const LootContainer &loot) :
			Creature('h', name, MEDIUM, health, color, rarity, loot){};
};

const LootContainer MAN_LOOT = LootContainer(std::vector<std::shared_ptr<Loot>>({
	std::shared_ptr<Loot>(new Loot(SWORD, 0.3))
}));
const EquipmentContainer MAN_EQUIPMENT = EquipmentContainer(std::vector<std::shared_ptr<Equipment>>({
	SWORD,
	LEATHER_BODY
}));
const EquipmentContainer EQUIPMENT_NONE = EquipmentContainer(std::vector<std::shared_ptr<Equipment>>({

}));
const Human MAN = Human("Man", TCODColor::lightestAmber, 30, RARITY_COMMON, MAN_LOOT);