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

	Weapon(std::string name, Glyph glyph, float weight, int damage, Type type) : Equipment(glyph, name, weight, type), damage(damage){};
};

const std::shared_ptr<Weapon> DAGGER = std::shared_ptr<Weapon>(new Weapon("Dagger", Glyph(TCODColor::grey, 'd'), 0.5, 2, Item::WEAPON_MELEE));
const std::shared_ptr<Weapon> SWORD = std::shared_ptr<Weapon>(new Weapon("Sword", Glyph(TCODColor::grey, 's'), 4.0, 8, Item::WEAPON_MELEE));

const std::shared_ptr<Weapon> BOW = std::shared_ptr<Weapon>(new Weapon("Bow", Glyph(TCODColor::grey, 'B'), 3.0, 5, Item::WEAPON_RANGED));
