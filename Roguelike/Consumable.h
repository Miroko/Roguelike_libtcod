#pragma once
#include "Item.h"
#include "CreatureEffect.h"
#include <vector>

class Consumable : public Item
{
public:
	virtual void onConsume(Creature &consumer) = 0;

	Consumable(std::string name, Glyph glyph, float weight, Type type, RarityType &rarity) :
		Item(name, glyph, weight, type, rarity){};
};