#pragma once
#include "Equipment.h"
class Weapon : public Equipment
{
public:
	int damage;

	Weapon(Glyph glyph, std::string name, float weight, int damage) : Equipment(glyph, name, weight, WEAPON), damage(damage){};
};

class Sword : public Weapon{
public:
	Sword() : Weapon(Glyph(TCODColor::grey, 's'), "a sword", 3.0, 10){};
};

