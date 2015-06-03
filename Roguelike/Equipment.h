#pragma once
#include "Item.h"
class Equipment : public Item
{
public:
	Equipment(Glyph glyph, std::string name, float weight, Type type) : Item(glyph, name, weight, type){};
};