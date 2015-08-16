#include "TradeContainer.h"
#include "Armor.h"
#include "Weapon.h"
#include "Engine.h"

TradeContainer TradeContainer::EMPTY = TradeContainer(0, 0, 0, 0);

void TradeContainer::generateItems(){
	//remove old
	items.removeAll();

	//set currency
	currentCurrency = currency;

	//genereate new items
	for (int weaponRoll = weaponRolls; weaponRoll> 0; --weaponRoll){
		int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.weaponTemplates.size() - 1);
		auto &hashmapIterator = engine::objectLibrary.weaponTemplates.begin();
		std::advance(hashmapIterator, randomIndex);
		TemplateWeapon &randomTemplate = hashmapIterator->second;
		auto &weapon = engine::objectFactory.createWeapon(randomTemplate, *engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()));
		items.add(std::static_pointer_cast<Item>(weapon));
	}
	for (int armorRoll = armorRolls; armorRoll > 0; --armorRoll){
		int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.armorTemplates.size() - 1);
		auto &hashmapIterator = engine::objectLibrary.armorTemplates.begin();
		std::advance(hashmapIterator, randomIndex);
		TemplateArmor &randomTemplate = hashmapIterator->second;
		auto &armor = engine::objectFactory.createArmor(randomTemplate, *engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()));
		items.add(std::static_pointer_cast<Item>(armor));
	}
	for (int consumableRoll = consumableRolls; consumableRoll > 0; --consumableRoll){
		int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.consumableTemplates.size() - 1);
		auto &hashmapIterator = engine::objectLibrary.consumableTemplates.begin();
		std::advance(hashmapIterator, randomIndex);
		TemplateConsumable &randomTemplate = hashmapIterator->second;
		auto &consumable = engine::objectFactory.createConsumable(randomTemplate, *engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll()));
		items.add(std::static_pointer_cast<Item>(consumable));
	}
}
