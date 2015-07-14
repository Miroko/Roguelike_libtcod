#pragma once
#include "Glyph.h"
#include "Item.h"
#include <string>

class TemplatePotion
{
public:
	std::string id;
	std::string name;
	Glyph glyph;
	float weight;
	std::vector<std::shared_ptr<CreatureEffect>> effects;
	int duration;
	int potency;
	Item::Type type;

	TemplatePotion(std::string id, std::string name, Glyph glyph, float weight, std::vector<std::shared_ptr<CreatureEffect>> effects, int duration, int potency) :
		id(id), name(name), glyph(glyph), weight(weight), type(GameObject::POTION), effects(effects), duration(duration), potency(potency){};
};

