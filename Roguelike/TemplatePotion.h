#pragma once
#include "Glyph.h"
#include "Item.h"
#include <string>

class TemplatePotion
{
public:
	std::string name;
	Glyph glyph;
	float weight;
	Item::Type type;
	std::vector<std::shared_ptr<CreatureEffect>> effects;
	int value;

	TemplatePotion(std::string name, Glyph glyph, float weight, std::vector<std::shared_ptr<CreatureEffect>> effects, int value) :
		name(name), glyph(glyph), weight(weight), type(GameObject::POTION), effects(effects), value(value){};
};

