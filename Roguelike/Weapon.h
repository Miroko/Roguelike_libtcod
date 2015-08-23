#pragma once
#include "Equipment.h"

class WeaponAction;
class Weapon : public Equipment
{
private:
	int damage;

public:
	int range;

	std::vector<WeaponAction*> actions;

	std::string getStatistics();
	int getValue();
	int getDamage();

	Weapon(Equipment equipment, int damage, int range, std::vector<WeaponAction*> actions) :
		Equipment(equipment),
		damage(damage),
		range(range),
		actions(actions){};
};

