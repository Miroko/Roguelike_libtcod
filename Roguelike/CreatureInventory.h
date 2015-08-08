#pragma once
#include "ItemContainer.h"
#include "Consumable.h"

class Creature;
class Weapon;
class Armor;
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
	bool isEquipped(std::shared_ptr<Item> item);
	std::vector<Item*> getHoldingItems();
	std::vector<Weapon*> getWeapons();
	std::vector<Armor*> getArmors();
	int getTotalDefence();
	float getTotalEquippedWeight();
	float getTotalWeight();

	void init(Creature &owner);

	CreatureInventory(){};
};

