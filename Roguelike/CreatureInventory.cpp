#include "CreatureInventory.h"
#include "Creature.h"
#include "Armor.h"
#include "Weapon.h"
#include "Accessory.h"
#include "Consumable.h"
#include "Engine.h"

bool CreatureInventory::equip(std::shared_ptr<Item> item){
	if (item->isArmor()) return equipArmor(std::static_pointer_cast<Armor>(item));
	else if (item->isAccessory()) return equipAccessory(std::static_pointer_cast<Accessory>(item));
	else if (item->isWeapon()) return holdItem(item);
	return false;
}
void CreatureInventory::unequip(std::shared_ptr<Item> item){
	if (item->isArmor()) unequipArmor(std::static_pointer_cast<Armor>(item));
	else if (item->isAccessory()) unequipAccessory(std::static_pointer_cast<Accessory>(item));
	else if (item->isWeapon()) unholdItem(item);
	//remove stat stacking
	owner->healthHit(0);
	owner->staminaHit(0);
	owner->magicHit(0);
}
void CreatureInventory::consume(std::shared_ptr<Consumable> consumable){
	consumable->onConsume(*owner);
	items.remove(consumable);
}
void CreatureInventory::drop(std::shared_ptr<Item> item){
	if (isEquipped(item)) unequip(item);
	items.remove(item);
	engine::areaHandler.getCurrentArea()->placeItem(item, owner->location);
}
bool CreatureInventory::isEquipped(std::shared_ptr<Item> item){
	for (auto &limb : owner->limbs){
		if (limb.currentArmor == item) return true;
		else if (limb.currentItemInHold == item) return true;
		else if (limb.currentAccessories.contains(item)) return true;
	}
	return false;
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
bool CreatureInventory::equipAccessory(std::shared_ptr<Accessory> accessory){
	for (auto &limb : owner->limbs){
		if (limb.accessoryType == accessory->type){
			if ((int)limb.currentAccessories.items.size() < limb.accessoriesMaxAmount){
				limb.currentAccessories.add(accessory);
				return true;
			}
		}
	}
	return false;
}
bool CreatureInventory::unequipAccessory(std::shared_ptr<Accessory> accessory){
	for (auto &limb : owner->limbs){
		if (limb.accessoryType == accessory->type){
			if (limb.currentAccessories.contains(accessory)){
				limb.currentAccessories.remove(accessory);
				return true;
			}
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
std::vector<Weapon*> CreatureInventory::getEquippedWeapons(){
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
std::vector<Armor*> CreatureInventory::getEquippedArmors(){
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
std::vector<Accessory*> CreatureInventory::getAccessories(){
	std::vector<Accessory*> accessories;
	for (auto &limb : owner->limbs){
		for (auto &accessory : limb.currentAccessories.items){
			accessories.push_back(static_cast<Accessory*>(accessory.get()));
		}
	}
	return accessories;
}
int CreatureInventory::getTotalDefence(){
	int totalDefence = 0;
	for (auto &armor : getEquippedArmors()){
		totalDefence += armor->getDefenceTotal();
	}
	return totalDefence;
}
double CreatureInventory::getTotalEquippedWeight(){
	double totalWeight = 0;
	for (auto &armor : getEquippedArmors()){
		totalWeight += armor->getWeightTotal();
	}
	for (auto &weapon : getEquippedWeapons()){
		totalWeight += weapon->getWeightTotal();
	}
	for (auto &accessory : getAccessories()){
		totalWeight += accessory->getWeightTotal();
	}
	return totalWeight;
}
double CreatureInventory::getTotalWeight(){
	double totalWeight = 0;
	for (auto &item : items.items){
		totalWeight += item->getWeightTotal();
	}
	return totalWeight;
}
void CreatureInventory::init(Creature &owner){
	this->owner = &owner;
}