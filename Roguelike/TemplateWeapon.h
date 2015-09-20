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
	double durabilityFromMax;
	int limbsRequiredToHold;
	std::string skillId;

	TemplateWeapon(GameObject::Type type, std::string name, Glyph glyph, double weightKg, double damageFromMax,
		double durabilityFromMax, std::string skillId, int limbsRequiredToHold = 1) :
		name(name),
		glyph(glyph),
		weightKg(weightKg), 
		type(type),
		damageFromMax(damageFromMax),
		durabilityFromMax(durabilityFromMax),
		skillId(skillId),
		limbsRequiredToHold(limbsRequiredToHold){};
	TemplateWeapon(){}
};

