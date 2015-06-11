#pragma once
#include "libtcod.hpp"
class ItemSelector
{
public:

	TCODColor selectionColor = TCODColor::lighterGreen;

	int selectedRow = 0;

	bool handleKey(TCOD_key_t key);

	ItemSelector(){};
};

