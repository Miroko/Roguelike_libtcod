#pragma once
#include "Item.h"
#include "AliveObjectEffect.h"

class Consumable : public Item
{
public:
	std::vector<AliveObjectEffect*> effects;

	std::string getStatistics();

	int getValue();
	int getPotency();

	Consumable(std::string name, std::vector<AliveObjectEffect*> effects, Glyph glyph, float weight) :
		Item(name, glyph, weight, CONSUMABLE),
		effects(effects){};
};