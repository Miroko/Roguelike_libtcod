#pragma once
#include "Item.h"
#include "RarityType.h"
#include <vector>

class Equipment : public Item
{
public:
	Equipment(std::string name, Glyph glyph, float weight, Type type, RarityType &rarity) :
		Item(
		name,
		glyph,
		weight,
		type,
		rarity){};
};