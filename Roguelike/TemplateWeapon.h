#pragma once
#include "Glyph.h"
#include "Item.h"
#include <string>

class TemplateWeapon
{
public:
	std::string id;
	std::string name;
	Glyph glyph;
	float weight;
	Item::Type type;
	float damage;

	TemplateWeapon(std::string id, std::string name, Glyph glyph, float weight, float damage, Item::Type type) :
		id(id), name(name), glyph(glyph), weight(weight), type(type), damage(damage){};
};

