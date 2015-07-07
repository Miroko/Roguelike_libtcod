#include "ObjectFactory.h"
#include "TemplateCreature.h"
#include "TemplateCreaturePreset.h"
#include "AiMonster.h"
#include "Engine.h"
#include "Weapon.h"
#include "Door.h"
#include "Armor.h"

std::shared_ptr<Creature> ObjectFactory::createCreaturePreset(std::string creaturePresetTemplateId, RarityType &rarity){
	TemplateCreaturePreset &templateCreaturePreset = *engine::objectLibrary.getTemplateCreaturePreset(creaturePresetTemplateId);
	TemplateCreature &templateCreature = *engine::objectLibrary.getTemplateCreature(templateCreaturePreset.creatureTemplateId);
	std::shared_ptr<Creature> creature = std::shared_ptr<Creature>(new Creature(
		templateCreaturePreset.name,
		creaturePresetTemplateId,
		templateCreature.glyph,
		Creature::CREATURE,
		(int)((templateCreaturePreset.health / rarity.prevalence * engine::objectLibrary.maxHealth) *
			 (1.00f - engine::random.generator->getFloat(0.0, valueVariation))),
		rarity,
		rarity.getRandomCreatureMods(),
		engine::objectLibrary.getAi(templateCreaturePreset.AiId)->copy(),
		templateCreature.limbs));
	//ai
	creature->ai->owner = creature.get();
	//inventory
	creature->inventory.owner = creature.get();
	//change color
	creature->glyph.fgColor = creature->glyph.fgColor * rarity.color;
	for (auto &mod : creature->rarityMods){
		mod->apply(*creature);
	}
	//equip weapon
	for (auto &weaponId : templateCreaturePreset.weaponIds){
		auto &weapon = createWeapon(weaponId, rarity);
		creature->inventory.items.add(weapon);
		creature->inventory.equipWeapon(weapon);
	}
	//equip armor
	for (auto &armorId : templateCreaturePreset.armorIds){
		auto &armor = createArmor(armorId, rarity);
		creature->inventory.items.add(armor);
		creature->inventory.equipArmor(armor);
	}
	//store preset id in creature
	creature->presetId = creaturePresetTemplateId;
	return creature;
}
std::shared_ptr<Weapon> ObjectFactory::createWeapon(std::string weaponTemplateId, RarityType &rarity){
	TemplateWeapon &templateWeapon = *engine::objectLibrary.getTemplateWeapon(weaponTemplateId);
	std::shared_ptr<Weapon> weapon = std::shared_ptr<Weapon>(new Weapon(
		templateWeapon.name,
		templateWeapon.glyph,
		templateWeapon.weight * engine::objectLibrary.maxWeight,
		templateWeapon.type,
		(int)((templateWeapon.damage / rarity.prevalence * engine::objectLibrary.maxDamage) *
		     (1.00f - engine::random.generator->getFloat(0.0, valueVariation))),
		rarity,
		rarity.getRandomWeaponMods()
		));

	//rarity color
	weapon->glyph.fgColor = weapon->glyph.fgColor * rarity.color;

	//apply mods
	for (auto &mod : weapon->rarityMods){
		mod->apply(*weapon);
	}

	return weapon;
}
std::shared_ptr<Armor> ObjectFactory::createArmor(std::string armorTemplateId, RarityType &rarity){
	TemplateArmor &templateArmor = *engine::objectLibrary.getTemplateArmor(armorTemplateId);
	std::shared_ptr<Armor> armor = std::shared_ptr<Armor>(new Armor(
		templateArmor.name,
		templateArmor.glyph,
		templateArmor.weight * engine::objectLibrary.maxWeight,
		templateArmor.type,
		(int)((templateArmor.defence / rarity.prevalence * engine::objectLibrary.maxDefence) * 
			 (1.00f - engine::random.generator->getFloat(0.0, valueVariation))),
		rarity,
		rarity.getRandomArmorMods()
		));

	//rarity color
	armor->glyph.fgColor = armor->glyph.fgColor * rarity.color;

	//apply mods
	for (auto &mod : armor->rarityMods){
		mod->apply(*armor);
	}
	return armor;
}

std::shared_ptr<Door> ObjectFactory::createDoor(std::string doorId){
	return std::shared_ptr<Door>(new Door(*engine::objectLibrary.getDoor(doorId)));
}

std::shared_ptr<Creature> ObjectFactory::createCreaturePreset(std::string creaturePresetTemplateId, float rarityRoll){
	RarityType &rarity = *engine::objectLibrary.getRarity(rarityRoll);
	if (&rarity == nullptr) return nullptr;
	else return createCreaturePreset(creaturePresetTemplateId, rarity);
}
std::shared_ptr<Weapon> ObjectFactory::createWeapon(std::string weaponTemplateId, float rarityRoll){
	RarityType &rarity = *engine::objectLibrary.getRarity(rarityRoll);
	if (&rarity == nullptr) return nullptr;
	else return createWeapon(weaponTemplateId, rarity);
}
std::shared_ptr<Armor> ObjectFactory::createArmor(std::string armorTemplateId, float rarityRoll){
	RarityType &rarity = *engine::objectLibrary.getRarity(rarityRoll);
	if (&rarity == nullptr) return nullptr;
	else return createArmor(armorTemplateId, rarity);
}

void ObjectFactory::generateLootDrop(Creature &creature){
	std::vector<std::shared_ptr<Item>> lootItems;
	for (int dropNumber = lootDropRolls; dropNumber > 0; --dropNumber){
		if (engine::random.generator->getFloat(0.0, 1.0) > lootRollMiss){
			int type = engine::random.generator->getInt(0, 1);
			float rarityRoll = engine::random.generator->getFloat(0.0f, 1.0f) + (creature.rarity.prevalence * lootPrevalenceFromRarityRatio);
			if (type == 0){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.armorTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.armorTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateArmor &randomTemplate = hashmapIterator->second;
				auto &armor = engine::objectFactory.createArmor(randomTemplate.id, rarityRoll);
				if (armor != nullptr){
					lootItems.push_back(armor);
				}
			}
			else if (type == 1){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.weaponTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.weaponTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateWeapon &randomTemplate = hashmapIterator->second;
				auto &weapon = engine::objectFactory.createWeapon(randomTemplate.id, rarityRoll);
				if (weapon != nullptr){
					lootItems.push_back(weapon);
				}
			}
		}
	}
	for (auto &lootItem : lootItems){
		engine::areaHandler.getCurrentArea()->placeItem(lootItem, creature.location);
	}
}