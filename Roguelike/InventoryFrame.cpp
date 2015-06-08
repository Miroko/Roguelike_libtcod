#include "InventoryFrame.h"
#include "Engine.h"

void InventoryFrame::onItemSelect(std::shared_ptr<Item> item){
	useItem(item);
}

void InventoryFrame::useItem(std::shared_ptr<Item> item){
	switch (item->type){
	case Item::WEAPON: break;
	case Item::CONSUMABLE: break;
	default: break;
	}
	//items.remove(*items.items.at(selectionRow));
}

void InventoryFrame::equip(Weapon &weapon){
	Engine::playerHandler.playerCreature->weapon = &weapon;
}

void InventoryFrame::unEquip(Equipment *slot){
	slot = nullptr;
}