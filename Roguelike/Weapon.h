#pragma once
#include "Equipment.h"
#include "Random.h"
#include <memory>

class Weapon : public Equipment
{
public:
	int damage;

	Weapon(std::string name, Glyph glyph, float weight, int damage) : Equipment(glyph, name, weight, WEAPON), damage(damage){};
};

const Weapon DAGGER = Weapon("Dagger", Glyph(TCODColor::grey, 'd'), 1.0, 2);
const Weapon SWORD = Weapon("Sword", Glyph(TCODColor::grey, 's'), 1.0, 8);
