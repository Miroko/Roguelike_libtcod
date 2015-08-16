#include "ObjectFactory.h"
#include "Weapon.h"
#include "Door.h"
#include "Armor.h"
#include "Engine.h"

std::shared_ptr<Creature> ObjectFactory::createCreature(std::string id, std::string rarity){
	return createCreature(engine::objectLibrary.creaturePresetTemplates[id], *engine::raritySystem.getRarityType(rarity));
}

std::shared_ptr<Weapon> ObjectFactory::createWeapon(std::string id, std::string rarity){
	return createWeapon(engine::objectLibrary.weaponTemplates[id], *engine::raritySystem.getRarityType(rarity));
}

std::shared_ptr<Armor> ObjectFactory::createArmor(std::string id, std::string rarity){
	return createArmor(engine::objectLibrary.armorTemplates[id], *engine::raritySystem.getRarityType(rarity));
}

std::shared_ptr<Consumable> ObjectFactory::createConsumable(std::string id, std::string rarity){
	return createConsumable(engine::objectLibrary.consumableTemplates[id], *engine::raritySystem.getRarityType(rarity));
}

std::shared_ptr<OperatableObject> ObjectFactory::createOperatable(std::string id){
	return engine::objectLibrary.operatables[id]->copy();
}

std::shared_ptr<Creature> ObjectFactory::createCreature(TemplateCreaturePreset &presetTemplate, RarityType &rarityType){
	TemplateCreatureBase &templateCreatureBase = engine::objectLibrary.creatureBaseTemplates[presetTemplate.creatureBaseId];

	int health =
		(int)(engine::healthMax *
		presetTemplate.healthFromMax *
		rarityType.improvementMultiplier *
		engine::random.generator->getFloat(1.0f - engine::statisticVariation, 1.0f));

	int stamina =
		(int)(engine::staminaMax *
		presetTemplate.healthFromMax *
		rarityType.improvementMultiplier *
		engine::random.generator->getFloat(1.0f - engine::statisticVariation, 1.0f));

	std::shared_ptr<Creature> creature = std::shared_ptr<Creature>(new Creature(
		presetTemplate.id,
		//engine::raritySystem.getCreatureMod(rarityType),
		RarityMod(rarityType, { }),
		DynamicObject(GameObject(
		presetTemplate.name,
		Creature::CREATURE,
		presetTemplate.glyph),
		health),
		stamina, 
		engine::objectLibrary.ais[presetTemplate.aiId]->copy(),
		templateCreatureBase.limbs
		));

	//equip weapons
	for (auto &weaponId : presetTemplate.weaponIds){
		auto &weapon = createWeapon(engine::objectLibrary.weaponTemplates[weaponId], rarityType);
		creature->inventory.items.add(weapon);
		creature->inventory.holdItem(weapon);
	}
	//equip armors
	for (auto &armorId : presetTemplate.armorIds){
		auto &armor = createArmor(engine::objectLibrary.armorTemplates[armorId], rarityType);
		creature->inventory.items.add(armor);
		creature->inventory.equipArmor(armor);
	}
	return creature;
}
std::shared_ptr<Weapon> ObjectFactory::createWeapon(TemplateWeapon &weaponTemplate, RarityType &rarityType){
	int damage =
		(int)(engine::damageMax *
		weaponTemplate.damageFromMax *
		rarityType.improvementMultiplier *
		engine::random.generator->getFloat(1.0f - engine::statisticVariation, 1.0f));

	std::shared_ptr<Weapon> weapon = std::shared_ptr<Weapon>(new Weapon(
		Item(engine::raritySystem.getWeaponMod(rarityType),
		GameObject(
		weaponTemplate.name,
		weaponTemplate.type,
		weaponTemplate.glyph),
		weaponTemplate.weightKg,
		weaponTemplate.limbsRequiredToHold),
		damage,
		weaponTemplate.range
		));

	//rarity color
	weapon->glyph.fgColor = weapon->glyph.fgColor * rarityType.color;

	return weapon;
}
std::shared_ptr<Armor> ObjectFactory::createArmor(TemplateArmor &armorTemplate, RarityType &rarityType){
	int defence =
		(int)(engine::defenceMax *
		armorTemplate.defenceFromMax *
		rarityType.improvementMultiplier *
		engine::random.generator->getFloat(1.0f - engine::statisticVariation, 1.0f));

	std::shared_ptr<Armor> armor = std::shared_ptr<Armor>(new Armor(
		Item(engine::raritySystem.getArmorMod(rarityType),
		GameObject(
		armorTemplate.name,
		armorTemplate.type,
		armorTemplate.glyph),
		armorTemplate.weightKg,
		armorTemplate.limbsRequiredToHold),
		armorTemplate.limbsRequiredToEquip,
		defence
		));

	//rarity color
	armor->glyph.fgColor = armor->glyph.fgColor * rarityType.color;
	
	return armor;
}

std::shared_ptr<Consumable> ObjectFactory::createConsumable(TemplateConsumable &consumableTemplate, RarityType &rarityType){
	std::shared_ptr<Consumable> consumable = std::shared_ptr<Consumable>(new Consumable(
		Item(engine::raritySystem.getConsumableMod(rarityType),
		GameObject(
		consumableTemplate.name,
		consumableTemplate.type,
		consumableTemplate.glyph),
		consumableTemplate.weightKg
		)));

	//rarity color
	consumable->glyph.fgColor = consumable->glyph.fgColor * rarityType.color;

	return consumable;
}

void ObjectFactory::generateLootDrop(Creature &creature){
	std::vector<std::shared_ptr<Item>> lootItems;
	for (int dropNumber = engine::lootDropRolls; dropNumber > 0; --dropNumber){
		if (engine::random.chance(engine::lootRollDropChance)){
			int type = engine::random.generator->getInt(0, 2);
			RarityType &rarityType = *engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll(&creature));
			//armor
			if (type == 0){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.armorTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.armorTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateArmor &randomTemplate = hashmapIterator->second;
				auto &armor = createArmor(randomTemplate, rarityType);
				lootItems.push_back(armor);
			}
			//weapon
			else if (type == 1){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.weaponTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.weaponTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateWeapon &randomTemplate = hashmapIterator->second;
				auto &weapon = createWeapon(randomTemplate, rarityType);
				lootItems.push_back(weapon);
			}
			//consumable
			else if (type == 2){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.consumableTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.consumableTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateConsumable &randomTemplate = hashmapIterator->second;
				auto &consumable = createConsumable(randomTemplate, rarityType);
				lootItems.push_back(consumable);
			}
		}
	}
	for (auto &lootItem : lootItems){
		engine::areaHandler.getCurrentArea()->placeItem(lootItem, creature.location);
	}
}