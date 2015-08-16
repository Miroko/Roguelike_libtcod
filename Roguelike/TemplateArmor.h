#pragma once
#include "Glyph.h"
#include "GameObject.h"
#include <string>

class TemplateArmor
{
public:
	GameObject::Type type;
	std::string name;
	Glyph glyph;
	double weightKg;
	double defenceFromMax;
	int limbsRequiredToHold;
	int limbsRequiredToEquip;

	TemplateArmor(GameObject::Type type, std::string name, Glyph glyph, double weightKg, double defenceFromMax, int limbsRequiredToEquip = 1, int limbsRequiredToHold = 1) :
		name(name),
		glyph(glyph),
		weightKg(weightKg),
		type(type),
		defenceFromMax(defenceFromMax),
		limbsRequiredToEquip(limbsRequiredToEquip),
		limbsRequiredToHold(limbsRequiredToHold){};
	TemplateArmor(){}
};

