#include "TradeContainer.h"
#include "Armor.h"
#include "Weapon.h"
#include "Accessory.h"
#include "Consumable.h"
#include "Engine.h"

TradeContainer TradeContainer::EMPTY = TradeContainer(0, 0, 0, 0, 0);

void TradeContainer::generateItems(){
	//remove old
	items.removeAll();

	//set currency
	currentCurrency = currency;

	//genereate new items
	for (int weaponRoll = weaponRolls; weaponRoll> 0; --weaponRoll){
		items.add(
			std::static_pointer_cast<Item>(
			engine::objectFactory.createRandomWeapon(*engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()))));
	}
	for (int armorRoll = armorRolls; armorRoll > 0; --armorRoll){
		items.add(
			std::static_pointer_cast<Item>(
			engine::objectFactory.createRandomArmor(*engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()))));
	}
	for (int accessoryRoll = accessoryRolls; accessoryRoll> 0; --accessoryRoll){
		items.add(
			std::static_pointer_cast<Item>(
			engine::objectFactory.createRandomAccessory(*engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()))));
	}
	for (int consumableRoll = consumableRolls; consumableRoll > 0; --consumableRoll){
		items.add(
			std::static_pointer_cast<Item>(
			engine::objectFactory.createRandomConsumable(*engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()))));
	}
}
