#pragma once
#include "Weapon.h"
#include <vector>
class Loot
{
public:
	std::vector<Weapon> weapons;

	Loot(std::vector<Weapon> weapons) : weapons(weapons){};
};

