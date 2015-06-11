#include "InventoryFrame.h"
#include "Engine.h"

void InventoryFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	if (operation == EQUIP) equip(item);
	else if (operation == DROP) drop(item);
}

std::vector<std::string> InventoryFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	switch (item->type){
	case Item::WEAPON: return EQUIPMENT_OPERATIONS;
	case Item::CONSUMABLE: break;
	default: break;
	}
}

void InventoryFrame::equip(std::shared_ptr<Item> &item){
	std::shared_ptr<Item> temp = std::shared_ptr<Item>(item);
	Engine::GUI.equipment.unequip(temp);
	Engine::GUI.equipment.equip(temp);
	removeItem(temp);
}

void InventoryFrame::drop(std::shared_ptr<Item> &item){
	Engine::area.placeItem(item, Engine::playerHandler.playerCreature->location);
	removeItem(item);
}