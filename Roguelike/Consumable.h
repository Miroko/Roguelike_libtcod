#pragma once
#include "Item.h"
#include "CreatureEffect.h"
#include <vector>

class Consumable : public Item
{
public:
	std::vector<std::shared_ptr<CreatureEffect>> effects;

	std::string getStatistics();

	int getValue();
	int getPotency();

	Consumable(std::string name, std::vector<std::shared_ptr<CreatureEffect>> effects, Glyph glyph, float weight, RarityType &rarity) :
		Item(name, glyph, weight, CONSUMABLE, rarity),
		effects(effects){};
};