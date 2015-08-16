#pragma once
#include "Glyph.h"
#include "GameObject.h"
#include <string>

class TemplateConsumable
{
public:
	GameObject::Type type;
	std::string name;
	Glyph glyph;
	double weightKg;

	TemplateConsumable(GameObject::Type type, std::string name, Glyph glyph, double weightKg) :
		type(type),
		name(name),
		glyph(glyph),
		weightKg(weightKg){};
	TemplateConsumable(){}
};

