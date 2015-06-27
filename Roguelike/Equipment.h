#pragma once
#include "Item.h"

class Equipment : public Item
{
public:
	Equipment(std::string name, Glyph glyph, float weight, Type type) : Item(name, glyph, weight, type){};
	virtual ~Equipment(){};
};