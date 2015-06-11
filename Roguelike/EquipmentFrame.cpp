#include "EquipmentFrame.h"
#include "Engine.h"

void EquipmentFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	if (operation == UNEQUIP) unequip(item);
}

void EquipmentFrame::unequip(std::shared_ptr<Item> &item){	
	if (item->type == Item::WEAPON){
		if (weapon != nullptr){			
			Engine::GUI.inventory.addItem(weapon);			
			removeItem(weapon);
			Engine::playerHandler.playerCreature->weapon = nullptr;
			weapon = nullptr;
		}
	}	
}

void EquipmentFrame::equip(std::shared_ptr<Item> &item){
	addItem(item);

	if (item->type == Item::WEAPON){
		weapon = item;
		Engine::playerHandler.playerCreature->equip(weapon.get());
	}
}

std::vector<std::string> EquipmentFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	return EQUIPMENT_OPERATIONS;
}