#include "InventoryFrame.h"
#include "Engine.h"

void InventoryFrame::onItemSelect(std::shared_ptr<Item> item){
	useItem(item);
}

void InventoryFrame::useItem(std::shared_ptr<Item> item){
	switch (item->type){
	case Item::WEAPON: Engine::playerHandler.playerCreature->equip(static_cast<Equipment*>(item.get())); break;
	case Item::CONSUMABLE: break;
	default: break;
	}
}