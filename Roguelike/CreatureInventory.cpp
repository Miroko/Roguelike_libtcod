#include "CreatureInventory.h"
#include "Creature.h"
#include "Armor.h"
#include "Weapon.h"
#include "Engine.h"

void CreatureInventory::equipWeapon(std::shared_ptr<Weapon> weapon){
	currentWeapon = weapon;
}
void CreatureInventory::unequipWeapon(std::shared_ptr<Weapon> weapon){
	if (currentWeapon == weapon){
		currentWeapon = nullptr;
	}
}
void CreatureInventory::equipArmor(std::shared_ptr<Armor> armor){
	for (auto &limb : owner->limbs){
		if (limb.armorType == armor->type){
			limb.currentArmor = armor;
			break;
		}
	}
}
void CreatureInventory::unequipArmor(std::shared_ptr<Armor> armor){
	for (auto &limb : owner->limbs){
		if (limb.currentArmor == armor){
			limb.currentArmor = nullptr;
			break;
		}
	}
}
void CreatureInventory::consume(std::shared_ptr<Consumable> consumable){
	items.remove(consumable);
	if (consumable->type == Consumable::POTION){
		auto &potion = std::static_pointer_cast<Potion>(consumable);
		for (auto &effect : potion->effects){
			owner->addEffect(effect);
		}
	}
}
void CreatureInventory::drop(std::shared_ptr<Item> item){
	items.remove(item);
	engine::areaHandler.getCurrentArea()->placeItem(item, owner->location);
}
bool CreatureInventory::isEquipped(std::shared_ptr<Item> item){
	if (currentWeapon == item) return true;
	for (auto &limb : owner->limbs){
		if (limb.armorType == item->type){
			if (limb.currentArmor == item) return true;
		}
	}
	return false;
}
int CreatureInventory::getTotalDefence(){
	int totalDefence = 0;
	for (auto &limb : owner->limbs){
		if (limb.currentArmor != nullptr){
			totalDefence += limb.currentArmor->defence;
		}
	}
	return totalDefence;
}
float CreatureInventory::getTotalEquippedWeight(){
	float totalWeight = 0;
	if (currentWeapon != nullptr) totalWeight += currentWeapon->weight;
	for (auto &limb : owner->limbs){
		if (limb.currentArmor != nullptr){
			totalWeight += limb.currentArmor->weight;
		}
	}
	return totalWeight;
}
float CreatureInventory::getTotalWeight(){
	float totalWeight = 0;
	for (auto &item : items.items){
		totalWeight += item->weight;
	}
	return totalWeight;
}
void CreatureInventory::init(Creature &owner){
	this->owner = &owner;
}