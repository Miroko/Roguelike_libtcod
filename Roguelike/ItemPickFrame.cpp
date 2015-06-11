#include "ItemPickFrame.h"
#include "Engine.h"

bool ItemPickFrame::moveToInventory(std::shared_ptr<Item> &item){
	Engine::area.removeItem(*item);
	Engine::GUI.inventory.addItem(item);
	removeItem(item);
	return true;
}

void ItemPickFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	moveToInventory(item);
}

std::vector<std::string> ItemPickFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	return PICK_OPERATIONS;
}

void ItemPickFrame::onClose(){
	removeAll();
}