#pragma once
#include "libtcod.hpp"
#include "SelectableItemFrame.h"

class Item;
class InventoryFrame : public SelectableItemFrame
{
private:
	const TCODColor EQUIPPED_COLOR = TCODColor::darkestBlue;
	const std::string EQUIP = "Equip";
	const std::string UNEQUIP = "Unequip";
	const std::string CONSUME = "Consume";
	const std::string DROP = "Drop";
	const std::vector<std::string> EQUIPMENT_UNEQUIP_OPERATIONS = std::vector<std::string>({ UNEQUIP, DROP });
	const std::vector<std::string> EQUIPMENT_EQUIP_OPERATIONS = std::vector<std::string>({ EQUIP, DROP });
	const std::vector<std::string> CONSUMABLE_OPERATIONS = std::vector<std::string>({ CONSUME, DROP });

public:
	void onOpen();
	void render();

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation);
	std::vector<std::string> SelectableItemFrame::getOperationsForItem(std::shared_ptr<Item> &item);

	InventoryFrame(char controlKey, bool open, float alphaFg, float alphaBg) : 
		SelectableItemFrame(controlKey, open, alphaFg, alphaBg, "Inventory"){};
};
