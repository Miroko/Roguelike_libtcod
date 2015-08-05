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
void CreatureInventory::init(Creature &owner){
	this->owner = &owner;
}