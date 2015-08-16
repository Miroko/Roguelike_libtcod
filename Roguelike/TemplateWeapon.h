#pragma once
#include "Glyph.h"
#include "GameObject.h"
#include <string>

class TemplateWeapon
{
public:
	GameObject::Type type;
	std::string name;
	Glyph glyph;
	double weightKg;
	double damageFromMax;
	int range; // 1 for melee
	int limbsRequiredToHold;

	TemplateWeapon(GameObject::Type type, std::string name, Glyph glyph, double weightKg, double damageFromMax, int range = 1, int limbsRequiredToHold = 1) :
		name(name),
		glyph(glyph),
		weightKg(weightKg), 
		type(type),
		damageFromMax(damageFromMax),
		range(range),
		limbsRequiredToHold(limbsRequiredToHold){};
	TemplateWeapon(){}
};

