#include "LootContainer.h"
#include "Random.h"
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"

std::vector<std::shared_ptr<Item>> LootContainer::generateLoot() const{
	std::vector<std::shared_ptr<Item>> items;
	for (auto &loot : allLoot){
		if (loot->dropChance > 0){
			if (Random::generator.getFloat(0.0, 1.0) <= loot->dropChance){
				switch (loot->item->type){
				case Item::WEAPON_MELEE: items.push_back(Item::newItem(std::static_pointer_cast<Weapon>(loot->item))); break;
				case Item::WEAPON_RANGED: items.push_back(Item::newItem(std::static_pointer_cast<Weapon>(loot->item))); break;
				case Item::ARMOR_HEAD: items.push_back(Item::newItem(std::static_pointer_cast<Armor>(loot->item))); break;
				case Item::ARMOR_BODY: items.push_back(Item::newItem(std::static_pointer_cast<Armor>(loot->item))); break;
				case Item::ARMOR_HAND: items.push_back(Item::newItem(std::static_pointer_cast<Armor>(loot->item))); break;
				case Item::ARMOR_LEG: items.push_back(Item::newItem(std::static_pointer_cast<Armor>(loot->item))); break;
				case Item::CONSUMABLE: items.push_back(Item::newItem(std::static_pointer_cast<Consumable>(loot->item))); break;
				default: break;
				}
			}
		}
	}
	return items;
}