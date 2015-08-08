#include "CreatureInventory.h"
#include "Creature.h"
#include "Armor.h"
#include "Weapon.h"
#include "Engine.h"

bool CreatureInventory::equip(std::shared_ptr<Item> item){
	if (item->isArmor()) return engine::playerHandler.getPlayerCreature()->inventory.equipArmor(std::static_pointer_cast<Armor>(item));
	else if (item->isWeapon()) return engine::playerHandler.getPlayerCreature()->inventory.holdItem(item);
	return false;
}
void CreatureInventory::unequip(std::shared_ptr<Item> item){
	if (item->isArmor()) engine::playerHandler.getPlayerCreature()->inventory.unequipArmor(std::static_pointer_cast<Armor>(item));
	else if (item->isWeapon()) engine::playerHandler.getPlayerCreature()->inventory.unholdItem(item);
}
bool CreatureInventory::holdItem(std::shared_ptr<Item> item){
	std::vector<CreatureLimb*> limbsFree;
	for (auto &limb : owner->limbs){
		if (limb.canHold && limb.currentItemInHold == nullptr){
			limbsFree.push_back(&limb);
		}
	}
	if ((int)(limbsFree.size()) >= item->limbsRequiredToHold){
		for (int limbNumber = 0; limbNumber < item->limbsRequiredToHold; ++limbNumber){
			limbsFree.at(limbNumber)->currentItemInHold = item;
		}
		return true;
	}
	return false;
}
void CreatureInventory::unholdItem(std::shared_ptr<Item> item){
	for (auto &limb : owner->limbs){
		if (limb.currentItemInHold == item){
			limb.currentItemInHold = nullptr;
		}
	}
}
bool CreatureInventory::equipArmor(std::shared_ptr<Armor> armor){
	std::vector<CreatureLimb*> limbsFree;
	for (auto &limb : owner->limbs){
		if (limb.armorType == armor->type && limb.currentArmor == nullptr){
			limbsFree.push_back(&limb);
		}
	}
	if ((int)(limbsFree.size()) >= armor->limbsRequiredToEquip){
		for (int limbNumber = 0; limbNumber < armor->limbsRequiredToEquip; ++limbNumber){
			limbsFree.at(limbNumber)->currentArmor = armor;
		}
		return true;
	}
	return false;
}
void CreatureInventory::unequipArmor(std::shared_ptr<Armor> armor){
	for (auto &limb : owner->limbs){
		if (limb.currentArmor == armor){
			limb.currentArmor = nullptr;
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
	if (isEquipped(item)){
		if (item->isArmor()) unequipArmor(std::static_pointer_cast<Armor>(item));
		else if (item->isWeapon()) unholdItem(item);
	}
	items.remove(item);
	engine::areaHandler.getCurrentArea()->placeItem(item, owner->location);
}
bool CreatureInventory::isEquipped(std::shared_ptr<Item> item){
	for (auto &limb : owner->limbs){
		if (limb.currentArmor == item){
			return true;
		}
		else if (limb.currentItemInHold == item){
			return true;
		}
	}
	return false;
}
std::vector<Item*> CreatureInventory::getHoldingItems(){
	std::vector<Item*> items;
	for (auto &limb : owner->limbs){
		if (limb.currentItemInHold != nullptr){
			bool added = false;
			for (auto *item : items){
				if (item == limb.currentItemInHold.get()){
					added = true; break;
				}
			}
			if (!added){
				//if not already added from other holding limb
				items.push_back(limb.currentItemInHold.get());
			}
		}
	}
	return items;
}
std::vector<Weapon*> CreatureInventory::getWeapons(){
	std::vector<Weapon*> weapons;
	for (auto &limb : owner->limbs){
		if (limb.currentItemInHold != nullptr){
			if (limb.currentItemInHold->isWeapon()){
				bool added = false;
				for (auto *weapon : weapons){
					if (weapon == limb.currentItemInHold.get()){
						added = true; break;
					}
				}
				if (!added){
					weapons.push_back(static_cast<Weapon*>(limb.currentItemInHold.get()));
				}
			}
		}
	}
	return weapons;
}
std::vector<Armor*> CreatureInventory::getArmors(){
	std::vector<Armor*> armors;
	for (auto &limb : owner->limbs){
		if (limb.currentArmor != nullptr){
			bool added = false;
			for (auto &armor : armors){
				if (armor == limb.currentArmor.get()){
					added = true; break;
				}
			}
			if (!added){
				armors.push_back(static_cast<Armor*>(limb.currentArmor.get()));
			}
		}
	}
	return armors;
}
int CreatureInventory::getTotalDefence(){
	int totalDefence = 0;
	for (auto &armor : getArmors()){
		totalDefence += armor->defence;
	}
	return totalDefence;
}
float CreatureInventory::getTotalEquippedWeight(){
	float totalWeight = 0;
	for (auto &armor : getArmors()){
		totalWeight += armor->weight;
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