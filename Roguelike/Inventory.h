#pragma once
#include "libtcod.hpp"
#include "Item.h"
#include "Loot.h"
#include "vector"
#include "memory"
class Inventory
{
public:
	//Loot
	Loot loot;

	//GUI
	bool isOpen;
	std::shared_ptr<TCODConsole> console;
	void init();
	void openOrClose();
	void render();

	Inventory(){};
};

