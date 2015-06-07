#pragma once
#include "libtcod.hpp"
#include "GuiFrame.h"
#include "Item.h"
#include "ItemContainer.h"
#include "Weapon.h"
#include "vector"
#include "memory"
class Inventory : public GuiFrame
{
public:	
	ItemContainer<Weapon> weapons;
	//Weapon must be from inventory
	void equip(Weapon &equipment);
	//Slot must be from playerCreature
	void unEquip(Equipment *slot);

	void GuiFrame::render(float elapsed);
	bool GuiFrame::handleKey(TCOD_key_t key);

	Inventory(std::string name, bool open, float alphaFg, float alphaBg) : GuiFrame(name, open, alphaFg, alphaBg){};
};

