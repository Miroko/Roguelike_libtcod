#include "InventoryFrame.h"
#include "Engine.h"
#include "String.h"

void InventoryFrame::onOpen(){
	setItemContainer(engine::playerHandler.getPlayerCreature()->inventory.items);
	SelectableItemFrame::onOpen();
}

void InventoryFrame::onItemSelect(std::shared_ptr<Item> &item, std::string &operation){
	if (operation == EQUIP) engine::playerHandler.playerInventory.equip(std::static_pointer_cast<Equipment>(item));
	else if (operation == UNEQUIP) engine::playerHandler.playerInventory.unequip(std::static_pointer_cast<Equipment>(item));
	else if (operation == CONSUME) engine::playerHandler.playerInventory.consume(std::static_pointer_cast<Consumable>(item));
	else if (operation == DROP) engine::playerHandler.playerInventory.drop(item);
}

std::vector<std::string> InventoryFrame::getOperationsForItem(std::shared_ptr<Item> &item){
	if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(item)){
		switch (item->type){
		case Item::WEAPON_MELEE: return EQUIPMENT_UNEQUIP_OPERATIONS;
		case Item::WEAPON_RANGED: return EQUIPMENT_UNEQUIP_OPERATIONS;
		case Item::ARMOR_HEAD: return EQUIPMENT_UNEQUIP_OPERATIONS;
		case Item::ARMOR_BODY: return EQUIPMENT_UNEQUIP_OPERATIONS;
		case Item::ARMOR_HAND: return EQUIPMENT_UNEQUIP_OPERATIONS;
		case Item::ARMOR_LEG: return EQUIPMENT_UNEQUIP_OPERATIONS;
		case Item::CONSUMABLE: return EQUIPMENT_UNEQUIP_OPERATIONS;
		default: return std::vector<std::string>({ "NONE" });
		}
	}
	else{
		switch (item->type){
		case Item::WEAPON_MELEE: return EQUIPMENT_EQUIP_OPERATIONS;
		case Item::WEAPON_RANGED: return EQUIPMENT_EQUIP_OPERATIONS;
		case Item::ARMOR_HEAD: return EQUIPMENT_EQUIP_OPERATIONS;
		case Item::ARMOR_BODY: return EQUIPMENT_EQUIP_OPERATIONS;
		case Item::ARMOR_HAND: return EQUIPMENT_EQUIP_OPERATIONS;
		case Item::ARMOR_LEG: return EQUIPMENT_EQUIP_OPERATIONS;
		case Item::CONSUMABLE: return EQUIPMENT_EQUIP_OPERATIONS;
		default: return std::vector<std::string>({ "NONE" });
		}		
	}
}

void InventoryFrame::render(){
	GuiFrame::render();

	//No items
	if (currentItemContainer->items.empty()){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 2, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_CENTER, "No items");
	}
	else{
		//Items
		int offsetY = 0;
		for (auto &item : currentItemContainer->items){
			//item
			printString(0, offsetY, getWidth(), 1, item->rarity.color, item->rarity.color, TCOD_LEFT, TCOD_BKGND_NONE, item->name);
			//stats
			printString(getWidth() / 2, offsetY, getWidth(), 1, FG_COLOR, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, item->getStatistics() + engine::string.currency(item->getValue()) + " " + engine::string.weight(item->weight));
			//operator
			if (offsetY == selectedRow){
				printString(0, offsetY, getWidth(), 1, OPERATION_COLOR, OPERATION_COLOR, TCOD_RIGHT, TCOD_BKGND_NONE, operations.at(selectedOperation));
				paintRowBg(SELECTION_COLOR, selectedRow);
			}
			else if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(item)){
				printString(0, offsetY, getWidth(), 1, OPERATION_COLOR, OPERATION_COLOR, TCOD_RIGHT, TCOD_BKGND_NONE, "Equipped");
				paintRowBg(EQUIPPED_COLOR, offsetY);
			}
			++offsetY;
		}
	}

	blit();
}
