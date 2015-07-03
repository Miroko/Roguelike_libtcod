#pragma once
#include "WeaponEffect.h"
#include <vector>
#include <memory>

class Weapon;
class RarityModWeapon
{
public:
	std::string name;
	std::vector<std::shared_ptr<WeaponEffect>> effects;

	void apply(Weapon &creature);

	RarityModWeapon(std::string name, std::vector<std::shared_ptr<WeaponEffect>> effects) :
		name(name), effects(effects){};
};

