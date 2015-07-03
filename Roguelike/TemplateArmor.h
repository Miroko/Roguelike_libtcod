#pragma once
#include "Glyph.h"
#include "Item.h"
#include <string>

class TemplateArmor
{
public:
	std::string id;
	std::string name;
	Glyph glyph;
	float weight;
	Item::Type type;
	float defence;

	TemplateArmor(std::string id, std::string name, Glyph glyph, float weight, float defence, Item::Type type) :
		id(id),
		name(name),
		glyph(glyph),
		weight(weight),
		type(type),
		defence(defence){};
};

