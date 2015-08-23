#pragma once
#include "Glyph.h"
#include "GameObject.h"
#include <vector>
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
	int range; // 1 for melee
	int limbsRequiredToHold;
	std::vector<std::string> actions;

	TemplateWeapon(GameObject::Type type, std::string name, Glyph glyph, double weightKg, double damageFromMax,
		double durabilityFromMax, std::vector<std::string> actions, int range = 1, int limbsRequiredToHold = 1) :
		name(name),
		glyph(glyph),
		weightKg(weightKg), 
		type(type),
		damageFromMax(damageFromMax),
		durabilityFromMax(durabilityFromMax),
		actions(actions),
		range(range),
		limbsRequiredToHold(limbsRequiredToHold){};
	TemplateWeapon(){}
};

