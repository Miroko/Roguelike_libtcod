#pragma once
#include <string>

class Weapon;
class WeaponEffect
{
public:
	virtual std::string getDescription() = 0;
	virtual void apply(Weapon &weapon) = 0;

	WeaponEffect(){};
};

