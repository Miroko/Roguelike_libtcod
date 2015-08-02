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
	int range; // 1 for melee

	TemplateWeapon(std::string id, std::string name, Glyph glyph, float weight, float damage, Item::Type type, int range = 1) :
		id(id),
		name(name),
		glyph(glyph),
		weight(weight), 
		type(type),
		damage(damage),
		range(range){};
};

