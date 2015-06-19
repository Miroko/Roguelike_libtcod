#include "ItemPickFrame.h"
#include "Engine.h"

bool ItemPickFrame::moveToInventory(std::shared_ptr<Item> &item){
	if (Engine::GUI.inventory.getCurrentWeight() + item->weight > MAX_WEIGHT) Engine::GUI.log.addMessage("I need to drop something first.");
	else{
		Engine::area.removeItem(*item);
		Engine::GUI.inventory.addItem(item);
		removeItem(item);
	}
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