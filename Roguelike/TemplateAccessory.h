#pragma once
#include <string>
#include "Glyph.h"

class TemplateAccessory
{
public:
	GameObject::Type type;
	std::string name;
	Glyph glyph;
	double weightKg;
	double spellPowerFromMax;

	TemplateAccessory(GameObject::Type type, std::string name, Glyph glyph, double weightKg, double spellPowerFromMax) :
		type(type),
		name(name),
		glyph(glyph),
		weightKg(weightKg),
		spellPowerFromMax(spellPowerFromMax){}
	TemplateAccessory(){}
};

