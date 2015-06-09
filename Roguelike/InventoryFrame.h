#pragma once
#include "libtcod.hpp"
#include "SelectableItemFrame.h"
#include "Item.h"
#include "Weapon.h"
#include <memory>

class InventoryFrame : public SelectableItemFrame<Item>
{

public:
	void useItem(std::shared_ptr<Item> item);

	void SelectableItemFrame<Item>::onItemSelect(std::shared_ptr<Item> item);

	InventoryFrame(std::string name, bool open, float alphaFg, float alphaBg) : SelectableItemFrame<Item>(name, open, alphaFg, alphaBg){};
};

