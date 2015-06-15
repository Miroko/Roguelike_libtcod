#pragma once
#include "libtcod.hpp"
#include "SelectableItemFrame.h"
#include "Item.h"
#include "Weapon.h"
#include <memory>

class InventoryFrame : public SelectableItemFrame
{
private:
	const std::string EQUIP = "Equip";
	const std::string CONSUME = "Consume";
	const std::string DROP = "Drop";
	const std::vector<std::string> EQUIPMENT_OPERATIONS = std::vector<std::string>({ EQUIP, DROP });
	const std::vector<std::string> CONSUMABLE_OPERATIONS = std::vector<std::string>({ CONSUME, DROP });
public:
	void equip(std::shared_ptr<Item> &item);
	void consume(std::shared_ptr<Item> &item);
	void drop(std::shared_ptr<Item> &item);

	void SelectableItemFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation);
	std::vector<std::string> SelectableItemFrame::getOperationsForItem(std::shared_ptr<Item> &item);

	InventoryFrame(std::string name, char controlKey, bool open, float alphaFg, float alphaBg) : SelectableItemFrame(name, controlKey, open, alphaFg, alphaBg){};
};
