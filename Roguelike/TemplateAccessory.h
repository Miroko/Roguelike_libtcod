#pragma once
#include <string>
#include "Glyph.h"

class TemplateAccessory
{
public:
	std::string name;
	Glyph glyph;
	double weightKg;
	double spellPowerFromMax;

	TemplateAccessory(std::string name, Glyph glyph, double weightKg, double spellPowerFromMax) :
		name(name),
		glyph(glyph),
		weightKg(weightKg),
		spellPowerFromMax(spellPowerFromMax){}
	TemplateAccessory(){}
};

