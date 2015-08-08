#include "ObjectFactory.h"
#include "TemplateCreature.h"
#include "TemplateCreaturePreset.h"
#include "TemplatePotion.h"
#include "TemplatePotionRarityMap.h"
#include "AiMonster.h"
#include "Engine.h"
#include "Weapon.h"
#include "Door.h"
#include "Armor.h"

std::shared_ptr<Creature> ObjectFactory::createCreaturePreset(std::string creaturePresetTemplateId, RarityType &rarity){
	TemplateCreaturePreset &templateCreaturePreset = *engine::objectLibrary.getTemplateCreaturePreset(creaturePresetTemplateId);
	TemplateCreature &templateCreature = *engine::objectLibrary.getTemplateCreature(templateCreaturePreset.creatureTemplateId);

	int health =
		(int)(engine::healthMax *
		templateCreaturePreset.health *
		rarity.improvementMultiplier *
		engine::random.generator->getFloat(1.0f - engine::valueVariation, 1.0f));

	int stamina = (int)(health * 0.8f);

	std::shared_ptr<Creature> creature = std::shared_ptr<Creature>(new Creature(
		templateCreaturePreset.name,
		creaturePresetTemplateId,
		templateCreaturePreset.glyph,
		Creature::CREATURE,
		health,
		stamina,
		rarity,
		rarity.getRandomCreatureMods(),
		engine::objectLibrary.getAi(templateCreaturePreset.AiId)->copy(),
		templateCreature.limbs));
	//ai
	creature->ai->owner = creature.get();
	//inventory
	creature->inventory.owner = creature.get();
	for (auto &mod : creature->rarityMods){
		mod->apply(*creature);
	}
	//equip weapon
	for (auto &weaponId : templateCreaturePreset.weaponIds){
		auto &weapon = createWeapon(weaponId, rarity);
		creature->inventory.items.add(weapon);
		creature->inventory.holdItem(weapon);
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
		templateWeapon.weight * engine::carryWeightMax,
		templateWeapon.type,
		templateWeapon.limbsRequiredToHold,
		(int)(engine::damageMax *
			 templateWeapon.damage *
			 rarity.improvementMultiplier *
			 engine::random.generator->getFloat(1.0f - engine::valueVariation, 1.0f)),
		templateWeapon.range,
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
		templateArmor.weight * engine::carryWeightMax,
		templateArmor.type,
		templateArmor.limbsRequiredToHold,
		templateArmor.limbsRequiredToEquip,
		(int)(engine::defenceMax *
			 templateArmor.defence *
		     rarity.improvementMultiplier * 
			 engine::random.generator->getFloat(1.0f - engine::valueVariation, 1.0f)),
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

std::shared_ptr<Potion> ObjectFactory::createPotion(TemplatePotionRarityMap &rarityMap, RarityType &rarityType){
	TemplatePotion *templatePotion = rarityMap.getPotionTemplate(rarityType.id);
	if (templatePotion != nullptr){
		//clone effects in template
		std::vector<std::shared_ptr<CreatureEffect>> clonedEffects;
		for (auto &effect : templatePotion->effects){
			clonedEffects.push_back(effect->clone());
		}

		std::shared_ptr<Potion> newPotion = std::shared_ptr<Potion>(new Potion(
		templatePotion->name,
		templatePotion->glyph,
		templatePotion->weight * engine::carryWeightMax,
		clonedEffects,
		templatePotion->value,
		rarityType));
		return newPotion;
	}
	else return nullptr;
}

std::shared_ptr<OperatableObject> ObjectFactory::createOperatable(std::string operatableId){
	return engine::objectLibrary.getOperatable(operatableId)->copy();
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
std::shared_ptr<Potion> ObjectFactory::createPotion(std::string rarityMapId, float rarityRoll){
	TemplatePotionRarityMap &rarityMap = *engine::objectLibrary.getPotionRarityMap(rarityMapId);
	RarityType &rarity = *engine::objectLibrary.getRarity(rarityRoll);
	if (&rarity == nullptr) return nullptr;
	else return createPotion(rarityMap, rarity);
}

void ObjectFactory::generateLootDrop(Creature &creature){
	std::vector<std::shared_ptr<Item>> lootItems;
	for (int dropNumber = engine::lootDropRolls; dropNumber > 0; --dropNumber){
		if (engine::random.generator->getFloat(0.0, 1.0) > engine::lootRollMissChance){
			int type = engine::random.generator->getInt(0, 2);
			float rarityRoll = engine::random.generator->getFloat(0.0f, 1.0f - ((1.0f - creature.rarity.prevalence) * engine::lootRarityFromCreatureRarityRatio));
			RarityType &rarity = *engine::objectLibrary.getRarity(rarityRoll);
			//armor
			if (type == 0){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.armorTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.armorTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateArmor &randomTemplate = hashmapIterator->second;
				auto &armor = createArmor(randomTemplate.id, rarityRoll);
				if (armor != nullptr){
					lootItems.push_back(armor);
				}
			}
			//weapon
			else if (type == 1){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.weaponTemplates.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.weaponTemplates.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplateWeapon &randomTemplate = hashmapIterator->second;
				auto &weapon = createWeapon(randomTemplate.id, rarityRoll);
				if (weapon != nullptr){
					lootItems.push_back(weapon);
				}
			}
			//potion
			else if (type == 2){
				int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.potionRarityMaps.size() - 1);
				auto &hashmapIterator = engine::objectLibrary.potionRarityMaps.begin();
				std::advance(hashmapIterator, randomIndex);
				TemplatePotionRarityMap &randomRarityMap = hashmapIterator->second;
				auto &potion = createPotion(randomRarityMap, rarity);
				if (potion != nullptr){
					lootItems.push_back(potion);
				}
			}
		}
	}
	for (auto &lootItem : lootItems){
		engine::areaHandler.getCurrentArea()->placeItem(lootItem, creature.location);
	}
}