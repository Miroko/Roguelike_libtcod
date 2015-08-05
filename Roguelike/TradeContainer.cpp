#include "TradeContainer.h"
#include "Armor.h"
#include "Weapon.h"
#include "Potion.h"
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
		float rarityRoll = engine::random.generator->getFloat(0.0f, 1.0f);
		auto &weapon = engine::objectFactory.createWeapon(randomTemplate.id, rarityRoll);
		if (weapon != nullptr){
			items.add(std::static_pointer_cast<Item>(weapon));
		}
	}
	for (int armorRoll = armorRolls; armorRoll > 0; --armorRoll){
		int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.armorTemplates.size() - 1);
		auto &hashmapIterator = engine::objectLibrary.armorTemplates.begin();
		std::advance(hashmapIterator, randomIndex);
		TemplateArmor &randomTemplate = hashmapIterator->second;
		float rarityRoll = engine::random.generator->getFloat(0.0f, 1.0f);
		auto &armor = engine::objectFactory.createArmor(randomTemplate.id, rarityRoll);
		if (armor != nullptr){
			items.add(std::static_pointer_cast<Item>(armor));
		}
	}
	for (int potionRoll = potionRolls; potionRoll > 0; --potionRoll){
		int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.potionRarityMaps.size() - 1);
		auto &hashmapIterator = engine::objectLibrary.potionRarityMaps.begin();
		std::advance(hashmapIterator, randomIndex);
		TemplatePotionRarityMap &randomRarityMap = hashmapIterator->second;
		float rarityRoll = engine::random.generator->getFloat(0.0f, 1.0f);
		auto &potion = engine::objectFactory.createPotion(randomRarityMap, *engine::objectLibrary.getRarity(rarityRoll));
		if (potion != nullptr){
			items.add(std::static_pointer_cast<Item>(potion));
		}
	}
}
