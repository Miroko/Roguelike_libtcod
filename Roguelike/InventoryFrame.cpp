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
		case Item::POTION: return CONSUMABLE_OPERATIONS;
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
		case Item::POTION: return CONSUMABLE_OPERATIONS;
		default: return std::vector<std::string>({ "NONE" });
		}		
	}
}

void InventoryFrame::render(){
	GuiFrame::render();

	int offsetY = 0;
	//separating line
	console->printFrame(0, 0, console->getWidth(), 4, false, TCOD_BKGND_DEFAULT, title.c_str());
	//currency
	printString(0, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_LEFT, TCOD_BKGND_NONE, engine::string.currency(engine::playerHandler.playerInventory.currency));
	//weight
	printString(0, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_RIGHT, TCOD_BKGND_NONE, engine::string.weight(engine::playerHandler.playerInventory.getCurrentWeight()));
	offsetY += 3;

	//No items
	if (currentItemContainer->items.empty()){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 2, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_CENTER, "No items");
	}
	else{
		//Items
		int startIndex = selectedRow;
		if (startIndex > (int)(currentItemContainer->items.size() - getHeight() + offsetY - 1)){
			startIndex = currentItemContainer->items.size() - getHeight() + offsetY - 1;
			if (startIndex < 0) startIndex = 0;
		}
		int endIndex = startIndex + getHeight() - offsetY;
		if (endIndex >(int)(currentItemContainer->items.size() - 1)){
			endIndex = currentItemContainer->items.size() - 1;
		}
		auto &iterator = currentItemContainer->items.begin();
		std::advance(iterator, startIndex);
		for (int index = startIndex; index <= endIndex; ++index){
			auto item = *iterator;
			//item
			printString(0, offsetY, getWidth(), 1, item->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, item->rarity.color, TCOD_LEFT, TCOD_BKGND_NONE, item->name);
			//stats
			printString(getWidth() / 2, offsetY, getWidth(), 1, Gui::FRAME_FG, Gui::FRAME_FG, TCOD_LEFT, TCOD_BKGND_NONE, item->getStatistics() + engine::string.currency(item->getValue()) + " " + engine::string.weight(item->weight));
			//operator
			if (index == selectedRow){
				printString(0, offsetY, getWidth(), 1, Gui::SELECTABLE_OPERATION, Gui::SELECTABLE_OPERATION, TCOD_RIGHT, TCOD_BKGND_NONE, operations.at(selectedOperation));
				paintRowBg(Gui::SELECTABLE_BG, offsetY);
			}
			else if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(item)){
				printString(0, offsetY, getWidth(), 1, Gui::SELECTABLE_OPERATION, Gui::SELECTABLE_OPERATION, TCOD_RIGHT, TCOD_BKGND_NONE, "Equipped");
			}
			++offsetY;
			++iterator;
		}
	}

	blit();
}
