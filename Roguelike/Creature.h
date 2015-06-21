#pragma once
#include "AliveObject.h"
#include "RarityType.h"
#include "EquipmentContainer.h"

class Creature : public AliveObject
{
public:
	template <typename T> static std::shared_ptr<T> newCreature(const T &creatureTemplate, const EquipmentContainer &equipment){
		std::shared_ptr<T> creature = std::shared_ptr<T>(new T(creatureTemplate));
		equipment.equipOn(creature);
		return creature;
	}

	const RarityType &rarity;
	const EquipmentContainer &equipment;

	Creature(char character, std::string name, Size size, int health, const TCODColor &color, const RarityType &rarity, const LootContainer &loot) :
		rarity(rarity), equipment(equipment), AliveObject(Glyph(color * rarity.color, character), name, size, health, loot){};
};