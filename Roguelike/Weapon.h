#pragma once
#include "Equipment.h"
class Weapon : public Equipment
{
public:
	int damage;
	Weapon(Glyph glyph, std::string name, float weight, int damage) : Equipment(glyph, name, weight), damage(damage){};
};

class Sword : public Weapon{
public:
	Sword() : Weapon(Glyph(TCODColor::grey, '/'), "Sword", 3.0, 10){};
};

