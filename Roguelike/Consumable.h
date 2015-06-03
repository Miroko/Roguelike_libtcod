#pragma once
#include "Item.h"
class Consumable : public Item
{
public:
	Consumable(Glyph glyph, std::string name, unsigned short weight)
		: Item(glyph, name, weight, CONSUMABLE){};
};

