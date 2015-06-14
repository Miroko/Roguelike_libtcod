#pragma once
#include "Weapon.h"
#include <vector>
#include <memory>
class Loot
{
public:
	std::vector<std::shared_ptr<Weapon>> weapons;

	Loot(std::vector<std::shared_ptr<Weapon>> weapons) : weapons(weapons){};
};

