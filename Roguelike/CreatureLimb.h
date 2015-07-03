#pragma once
#include "GameObject.h"
#include <memory>

class Armor;
class Weapon;
class CreatureLimb
{
public:
	std::shared_ptr<Armor> currentArmor = nullptr;
	GameObject::Type armorType;
	std::string name;
	float hitChance;

	CreatureLimb(std::string name, float hitChance, GameObject::Type armorType) :
		name(name), hitChance(hitChance), armorType(armorType){};
};

