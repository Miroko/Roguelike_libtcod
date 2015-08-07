#include "PlayerInventory.h"
#include "Engine.h"
#include "Weapon.h"
#include "Armor.h"

void PlayerInventory::equip(std::shared_ptr<Equipment> item){
	if (item->isArmor()){
		engine::playerHandler.getPlayerCreature()->inventory.equipArmor(std::static_pointer_cast<Armor>(item));
	}
	else{
		engine::playerHandler.getPlayerCreature()->inventory.equipWeapon(std::static_pointer_cast<Weapon>(item));
	}
}

void PlayerInventory::unequip(std::shared_ptr<Equipment> item){
	if (item->isArmor()){
		engine::playerHandler.getPlayerCreature()->inventory.unequipArmor(std::static_pointer_cast<Armor>(item));
	}
	else{
		engine::playerHandler.getPlayerCreature()->inventory.unequipWeapon(std::static_pointer_cast<Weapon>(item));
	}
}

void PlayerInventory::consume(std::shared_ptr<Consumable> item){
	engine::playerHandler.getPlayerCreature()->inventory.consume(item);
}

void PlayerInventory::drop(std::shared_ptr<Item> item){
	if (item->isArmor() || item->isWeapon()){
		unequip(std::static_pointer_cast<Equipment>(item));
	}
	engine::playerHandler.getPlayerCreature()->inventory.drop(item);
}
