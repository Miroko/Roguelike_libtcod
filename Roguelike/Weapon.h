#pragma once
#include "Item.h"

class Weapon : public Item
{
private:
	int damage;

public:
	int range;

	std::string getStatistics();
	int getValue();
	int getDamage();

	Weapon(Item item, int damage, int range) :
		Item(item),
		damage(damage),
		range(range){};
};

