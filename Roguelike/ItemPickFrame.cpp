#include "ItemPickFrame.h"
#include "Engine.h"

bool ItemPickFrame::moveToInventory(std::shared_ptr<Item> &item){
	if (engine::playerHandler.playerInventory.getCurrentWeight() + item->weight > engine::playerHandler.playerInventory.MAX_WEIGHT){
		engine::gui.log.addMessage("I need to drop something first.");
	}
	else{
		engine::areaHandler.getCurrentArea()->removeItem(item);
		engine::playerHandler.getPlayerCreature()->inventory.items.add(item);
		currentItemContainer->remove(item);
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
	currentItemContainer->removeAll();
}