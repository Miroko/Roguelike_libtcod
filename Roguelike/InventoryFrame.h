#pragma once
#include "libtcod.hpp"
#include "SelectableItemFrame.h"
#include "Item.h"
#include "Weapon.h"
#include <memory>

class InventoryFrame : public SelectableItemFrame
{

public:	
	//Weapon must be from InventoryFrame
	void equip(Weapon &equipment);
	//Slot must be from playerCreature
	void unEquip(Equipment *slot);

	void useItem(std::shared_ptr<Item> item);

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> item);

	InventoryFrame(std::string name, bool open, float alphaFg, float alphaBg) : SelectableItemFrame(name, open, alphaFg, alphaBg){};
};

