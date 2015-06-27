#include "InventoryFrame.h"
#include "Engine.h"
#include "String.h"

float InventoryFrame::getCurrentWeight(){
	float currentWeight = 0;
	for (auto &item : items.items){
		currentWeight += item->weight;
	}
	for (auto &equipment : Engine::GUI.equipment.items.items){
		currentWeight += equipment->weight;
	}
	return currentWeight;
}

void InventoryFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	if (operation == EQUIP) equip(item);
	else if (operation == CONSUME) consume(item);
	else if (operation == DROP) drop(item);
}

std::vector<std::string> InventoryFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	switch (item->type){
	case Item::WEAPON_MELEE: return EQUIPMENT_OPERATIONS;
	case Item::WEAPON_RANGED: return EQUIPMENT_OPERATIONS;
	case Item::ARMOR_HEAD: return EQUIPMENT_OPERATIONS;
	case Item::ARMOR_BODY: return EQUIPMENT_OPERATIONS;
	case Item::ARMOR_HAND: return EQUIPMENT_OPERATIONS;
	case Item::ARMOR_LEG: return EQUIPMENT_OPERATIONS;
	case Item::CONSUMABLE: return CONSUMABLE_OPERATIONS;
	default: break;
	}
}

void InventoryFrame::equip(std::shared_ptr<Item> &item){
	std::shared_ptr<Item> temp = std::shared_ptr<Item>(item);
	Engine::GUI.equipment.unequip(temp);
	Engine::GUI.equipment.equip(temp);
	removeItem(temp);
}

void InventoryFrame::consume(std::shared_ptr<Item> &item){	
	Engine::playerController.playerCreature->consume(static_cast<Consumable&>(*item));
	removeItem(item);
}

void InventoryFrame::drop(std::shared_ptr<Item> &item){
	Engine::area.placeItem(item, Engine::playerController.playerCreature->location);
	removeItem(item);
}
