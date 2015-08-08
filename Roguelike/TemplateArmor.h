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
	int limbsRequiredToHold;
	int limbsRequiredToEquip;

	TemplateArmor(std::string id, std::string name, Glyph glyph, float weight, float defence, Item::Type type, int limbsRequiredToHold = 1, int limbsRequiredToEquip = 1) :
		id(id),
		name(name),
		glyph(glyph),
		weight(weight),
		type(type),
		defence(defence),
		limbsRequiredToEquip(limbsRequiredToEquip),
		limbsRequiredToHold(limbsRequiredToHold){};
};

