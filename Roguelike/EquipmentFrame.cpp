#include "EquipmentFrame.h"
#include "Engine.h"

void EquipmentFrame::onOpen(){
	
}

void EquipmentFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	if (operation == UNEQUIP) engine::playerHandler.playerInventory.unequip(std::static_pointer_cast<Equipment>(item));
}

std::vector<std::string> EquipmentFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	return EQUIPMENT_OPERATIONS;
}
