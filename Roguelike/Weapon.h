#pragma once
#include "Equipment.h"
#include "Random.h"
#include <memory>

class Weapon : public Equipment
{
public:
	int damage;

	std::string getDescription();
	int getValue();

	Weapon(std::string name, Glyph glyph, float weight, int damage) : Equipment(glyph, name, weight, WEAPON_MELEE), damage(damage){};
};

const std::shared_ptr<Weapon> DAGGER = std::shared_ptr<Weapon>(new Weapon("Dagger", Glyph(TCODColor::grey, 'd'), 0.5, 2));
const std::shared_ptr<Weapon> SWORD = std::shared_ptr<Weapon>(new Weapon("Sword", Glyph(TCODColor::grey, 's'), 3.0, 8));
