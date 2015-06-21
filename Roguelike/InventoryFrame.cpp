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
	Engine::playerController.playerCreature->consume(item);
	removeItem(item);
}

void InventoryFrame::drop(std::shared_ptr<Item> &item){
	Engine::area.placeItem(item, Engine::playerController.playerCreature->location);
	removeItem(item);
}

void InventoryFrame::render(float elapsed){
	//Frame
	GuiFrame::render(elapsed);
	if (items.items.empty()){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 2, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_CENTER, "No items");
	}

	//Currency + Weight 
	console->printFrame(0, 2, console->getWidth(), 1, true);
	console->printRectEx(1, 1, console->getWidth() - 2, 1, TCOD_BKGND_NONE, TCOD_LEFT, (std::to_string(currency) + "c").c_str());
	console->printRectEx(console->getWidth() - 2, 1, console->getWidth() - 2, 1, TCOD_BKGND_NONE, TCOD_RIGHT,
		(String::weight(getCurrentWeight()) + "/" + String::weight(MAX_WEIGHT) + "kg").c_str());
	blit();

	if (!items.items.empty()){
		//Items
		int y = 0;
		for (auto &item : items.items){
			if (y == selectedRow) console->setDefaultForeground(selectionColor);
			else console->setDefaultForeground(FG_COLOR);
			//Item
			console->printRectEx(1, y + 3, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_LEFT, item->getDescription().c_str());
			//Operation
			if (y == selectedRow){
				console->printRectEx(console->getWidth() - 2, y + 3, console->getWidth(), 1, TCOD_BKGND_NONE, TCOD_RIGHT, operations[selectedOperation].c_str());
			}

			blit(1, y + 3, console->getWidth() - 1, 1, bounds.start.x + 1, bounds.start.y + y + 3, alphaFg, alphaBg);
			++y;
		}
	}
}