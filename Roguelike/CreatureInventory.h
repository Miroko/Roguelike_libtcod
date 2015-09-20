#pragma once
#include "ItemContainer.h"
#include <vector>

class Creature;
class Weapon;
class Armor;
class Accessory;
class Consumable;
class WeaponAction;
class CreatureInventory
{
private:
	bool holdItem(std::shared_ptr<Item> item);
	void unholdItem(std::shared_ptr<Item> item);
	bool equipArmor(std::shared_ptr<Armor> armor);
	void unequipArmor(std::shared_ptr<Armor> armor);
	bool equipAccessory(std::shared_ptr<Accessory> accessory);
	bool unequipAccessory(std::shared_ptr<Accessory> accessory);

public:
	int currency = 0;
	Creature *owner;
	ItemContainer items;

	bool equip(std::shared_ptr<Item> item);
	void unequip(std::shared_ptr<Item> item);
	void consume(std::shared_ptr<Consumable> consumable);
	void drop(std::shared_ptr<Item> item);
	bool isEquipped(std::shared_ptr<Item> item);
	std::vector<Item*> getHoldingItems();
	std::vector<Weapon*> getWeapons();
	std::vector<Armor*> getArmors();
	std::vector<Accessory*> getAccessories();
	int getTotalDefence();
	double getTotalEquippedWeight();
	double getTotalWeight();

	void init(Creature &owner);

	CreatureInventory(){};
};

