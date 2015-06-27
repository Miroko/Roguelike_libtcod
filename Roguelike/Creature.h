#pragma once
#include "AliveObject.h"
#include "EquipmentContainer.h"

class RarityType;
class RarityEffect;
class Creature : public AliveObject
{
public:
	RarityType *rarity = nullptr;
	RarityEffect *rarityEffect = nullptr;

	void equip(EquipmentContainer &equipment);

	void update();

	Creature(std::string name, char character, const TCODColor &color, int health) :
		AliveObject(name, Glyph(color, character), health){};
};