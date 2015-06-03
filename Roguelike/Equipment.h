#pragma once
#include "Item.h"
class Equipment : public Item
{
public:
	Equipment(Glyph glyph, std::string name, float weight) : Item(glyph, name, weight){};
};