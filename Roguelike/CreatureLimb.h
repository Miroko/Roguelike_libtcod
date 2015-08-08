#pragma once
#include "GameObject.h"
#include <memory>

class Armor;
class Item;
class CreatureLimb
{
public:
	std::shared_ptr<Item> currentItemInHold = nullptr;
	std::shared_ptr<Armor> currentArmor = nullptr;
	GameObject::Type armorType;
	std::string name;
	float hitChance;
	bool canHold;

	CreatureLimb(std::string name, float hitChance, GameObject::Type armorType, bool canHold = false) :
		name(name), 
		hitChance(hitChance),
		armorType(armorType), 
		canHold(canHold){};
};

