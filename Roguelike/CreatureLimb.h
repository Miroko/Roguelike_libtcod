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
	GameObject::Type accessoryType;
	std::string name;
	double hitChance;
	bool canHold;
	int accessoriesMaxAmount;

	std::shared_ptr<Item> currentItemInHold = nullptr;
	std::shared_ptr<Armor> currentArmor = nullptr;
	ItemContainer currentAccessories;

	CreatureLimb(std::string name, double hitChance,
		GameObject::Type armorType, bool canHold = false,
		GameObject::Type accessoryType = GameObject::NONE, int accessoriesMaxAmount = 0) 
		:
		name(name), 
		hitChance(hitChance),
		armorType(armorType), 
		accessoryType(accessoryType),
		canHold(canHold),
		accessoriesMaxAmount(accessoriesMaxAmount){};
};

