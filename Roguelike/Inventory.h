#pragma once
#include "libtcod.hpp"
#include "Item.h"
#include "ItemContainer.h"
#include "Weapon.h"
#include "vector"
#include "memory"
class Inventory
{
public:
	
	ItemContainer<Weapon> weapons;
	//Weapon must be from inventory
	void equip(Weapon &equipment);
	//Slot must be from playerCreature
	void unEquip(Equipment *slot);

	//GUI
	bool isOpen;
	std::shared_ptr<TCODConsole> console;
	void init(bool open);
	void openOrClose();
	void render();

	//Input
	bool handleKey(TCOD_key_t key);

	Inventory(){};
};

