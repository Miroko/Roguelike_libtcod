#pragma once
#include "WeaponEffect.h"
#include <memory>

class Weapon;
class RarityModWeapon
{
public:
	std::string name;
	std::shared_ptr<WeaponEffect> effect;

	void apply(Weapon &creature);

	RarityModWeapon(std::shared_ptr<WeaponEffect> effect) : effect(effect){};
};

