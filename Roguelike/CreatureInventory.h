#pragma once
#include "ItemContainer.h"

class Creature;
class Weapon;
class Armor;
class Consumable;
class WeaponAction;
class CreatureInventory
{
public:
	int currency = 0;
	Creature *owner;
	ItemContainer items;

	bool equip(std::shared_ptr<Item> item);
	void unequip(std::shared_ptr<Item> item);
	bool holdItem(std::shared_ptr<Item> item);
	void unholdItem(std::shared_ptr<Item> item);
	bool equipArmor(std::shared_ptr<Armor> armor);
	void unequipArmor(std::shared_ptr<Armor> armor);
	void consume(std::shared_ptr<Consumable> consumable);
	void drop(std::shared_ptr<Item> item);
	bool isEquipped(Item &item);
	std::vector<Item*> getHoldingItems();
	std::vector<Weapon*> getWeapons();
	std::vector<Armor*> getArmors();
	int getTotalDefence();
	double getTotalEquippedWeight();
	double getTotalWeight();

	void init(Creature &owner);

	CreatureInventory(){};
};

