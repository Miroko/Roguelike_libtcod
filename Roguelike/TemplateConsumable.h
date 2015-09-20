#pragma once
#include "Glyph.h"
#include "GameObject.h"
#include <string>

class CreatureEffect;
class TemplateConsumable
{
public:
	std::string name;
	Glyph glyph;
	double weightKg;
	double potencyFromMax;
	double concentrationFromMax;

	TemplateConsumable(std::string name, Glyph glyph, double weightKg, double potencyFromMax, double concentrationFromMax) :
		name(name),
		glyph(glyph),
		weightKg(weightKg),
		potencyFromMax(potencyFromMax),
		concentrationFromMax(concentrationFromMax){};
	TemplateConsumable(){}
};

