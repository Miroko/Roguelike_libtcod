#pragma once
#include "AliveObject.h"
#include "RarityType.h"

class Creature : public AliveObject
{
public:
	const RarityType &rarity;	

	template <typename T> static std::shared_ptr<T> newCreature(const T &creatureTemplate, bool equip = true){
		std::shared_ptr<T> creature = std::shared_ptr<T>(new T(creatureTemplate));
		if (equip){
			creature->equip(creature->loot.weapons.at(0).get());
		}
		return creature;
	}

	Creature(char character, std::string name, Size size, int health, const TCODColor &color, const RarityType &rarity, const Loot &loot) :
		rarity(rarity), AliveObject(Glyph(color * rarity.color, character), name, size, health, loot){};
};