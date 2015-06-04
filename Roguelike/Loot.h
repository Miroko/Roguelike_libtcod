#pragma once
#include "Weapon.h"
#include <memory>
#include <vector>
class Loot
{
public:
	std::vector<Weapon> weapons;

	Loot(std::vector<Weapon> weapons) : weapons(weapons){};
	Loot(){};
};