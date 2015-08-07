#pragma once
#include "ItemContainer.h"
#include "Consumable.h"

class Creature;
class Weapon;
class Armor;
class CreatureInventory
{
public:
	Creature *owner;
	ItemContainer items;
	std::shared_ptr<Weapon> currentWeapon;

	void equipWeapon(std::shared_ptr<Weapon> weapon);
	void unequipWeapon(std::shared_ptr<Weapon> weapon);
	void equipArmor(std::shared_ptr<Armor> armor);
	void unequipArmor(std::shared_ptr<Armor> armor);
	void consume(std::shared_ptr<Consumable> consumable);
	void drop(std::shared_ptr<Item> item);
	bool isEquipped(std::shared_ptr<Item> item);
	int getTotalDefence();
	float getTotalEquippedWeight();
	float getTotalWeight();

	void init(Creature &owner);

	CreatureInventory(){};
};

