#include "ItemPickFrame.h"
#include "Engine.h"

#include <iostream>

bool ItemPickFrame::moveToInventory(std::shared_ptr<Item> item){
	Engine::area.removeItem(*items.items.at(selectedRow));
	Engine::GUI.inventory.items.add(items.items.at(selectedRow));
	removeSelectedItem();
	return true;
}

void ItemPickFrame::onItemSelect(std::shared_ptr<Item> item){
	moveToInventory(item);
}