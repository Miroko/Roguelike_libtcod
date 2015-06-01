#pragma once
#include "DynamicObject.h"
class Item : public DynamicObject
{
public:
	unsigned short weight;

	Item(Glyph glyph, std::string name,unsigned short weight)
		: DynamicObject(glyph, name, SMALL), weight(weight){};
};

