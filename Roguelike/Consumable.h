#pragma once
#include "Item.h"

class Consumable : public Item
{
public:

	Consumable(std::string name, Glyph glyph, float weight)
		: Item(glyph, name, weight, CONSUMABLE){};
};

const Consumable HEALTH_POTION = Consumable("Health potion", Glyph(TCODColor::lightRed, 'p'), 0.2);
