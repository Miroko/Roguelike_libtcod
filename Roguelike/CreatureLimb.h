#pragma once
#include "GameObject.h"
#include "ItemContainer.h"
#include <memory>
#include <vector>

class Item;
class Armor;
class Accessory;
class CreatureLimb
{
public:
	GameObject::Type armorType;
	std::string name;
	double hitChance;
	bool canHold;
	int accessoriesMaxAmount;

	std::shared_ptr<Item> currentItemInHold = nullptr;
	std::shared_ptr<Armor> currentArmor = nullptr;
	ItemContainer currentAccessories;

	CreatureLimb(std::string name, double hitChance, GameObject::Type armorType, int accessoriesMaxAmount = 1, bool canHold = false) :
		name(name), 
		hitChance(hitChance),
		armorType(armorType), 
		canHold(canHold),
		accessoriesMaxAmount(accessoriesMaxAmount){};
};

