#include "ObjectFactory.h"
#include "Weapon.h"
#include "Door.h"
#include "Armor.h"
#include "Accessory.h"
#include "Consumable.h"
#include "VisualEffect.h"
#include "ParticleSplash.h"
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

std::shared_ptr<Accessory> ObjectFactory::createAccessory(std::string id, std::string rarity){
	return createAccessory(engine::objectLibrary.accessoryTemplates[id], *engine::raritySystem.getRarityType(rarity));
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
		engine::random.variationMultiplier(engine::statisticVariation));

	int stamina =
		(int)(engine::staminaMax *
		presetTemplate.healthFromMax *
		rarityType.improvementMultiplier *
		engine::random.variationMultiplier(engine::statisticVariation));

	int magic =
		(int)(engine::magicMax *
		presetTemplate.magicFromMax *
		rarityType.improvementMultiplier *
		engine::random.variationMultiplier(engine::statisticVariation));

	std::shared_ptr<Creature> creature = std::shared_ptr<Creature>(new Creature(
		presetTemplate.id,
		RarityMod(rarityType, { }), //engine::raritySystem.getCreatureMod(rarityType)
		DynamicObject(GameObject(
		presetTemplate.name,
		Creature::CREATURE,
		presetTemplate.glyph),
		health,
		true,
		templateCreatureBase.visualEffectOnTakeDamage),
		stamina,
		magic,
		engine::objectLibrary.ais[presetTemplate.aiId]->copy(),
		templateCreatureBase.limbs
		));

	//equip weapons
	for (auto &weaponId : presetTemplate.weaponIds){
		auto &weapon = createWeapon(engine::objectLibrary.weaponTemplates[weaponId], rarityType);
		creature->inventory.items.add(weapon);
		creature->inventory.equip(weapon);
	}
	//equip armors
	for (auto &armorId : presetTemplate.armorIds){
		auto &armor = createArmor(engine::objectLibrary.armorTemplates[armorId], rarityType);
		creature->inventory.items.add(armor);
		creature->inventory.equip(armor);
	}
	return creature;
}
std::shared_ptr<Weapon> ObjectFactory::createWeapon(TemplateWeapon &weaponTemplate, RarityType &rarityType){
	int damage =
		(int)(engine::damageMax *
		weaponTemplate.damageFromMax *
		rarityType.improvementMultiplier *
		engine::random.variationMultiplier(engine::statisticVariation));

	double durability = 
		engine::durabilityMax * 
		weaponTemplate.durabilityFromMax *
		engine::random.variationMultiplier(engine::statisticVariation);

	std::shared_ptr<Weapon> weapon = std::shared_ptr<Weapon>(new Weapon(
		Equipment(Item(engine::raritySystem.getWeaponMod(rarityType),
		GameObject(
		weaponTemplate.name,
		weaponTemplate.type,
		weaponTemplate.glyph),
		weaponTemplate.weightKg,
		weaponTemplate.limbsRequiredToHold),
		durability),
		damage,
		*engine::objectLibrary.creatureSkills[weaponTemplate.skillId]
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
		engine::random.variationMultiplier(engine::statisticVariation));

	double durability =
		engine::durabilityMax *
		armorTemplate.durabilityFromMax *
		engine::random.variationMultiplier(engine::statisticVariation);

	std::shared_ptr<Armor> armor = std::shared_ptr<Armor>(new Armor(
		Equipment(Item(engine::raritySystem.getArmorMod(rarityType),
		GameObject(
		armorTemplate.name,
		armorTemplate.type,
		armorTemplate.glyph),
		armorTemplate.weightKg,
		armorTemplate.limbsRequiredToHold),
		durability),
		armorTemplate.limbsRequiredToEquip,
		defence
		));

	//rarity color
	armor->glyph.fgColor = armor->glyph.fgColor * rarityType.color;
	
	return armor;
}

std::shared_ptr<Accessory> ObjectFactory::createAccessory(TemplateAccessory &accessoryTemplate, RarityType &rarityType){
	double spellPower =
		engine::magicSpellPowerMax *
		accessoryTemplate.spellPowerFromMax *
		rarityType.improvementMultiplier *
		engine::random.variationMultiplier(engine::statisticVariation);

	std::shared_ptr<Accessory> accessory = std::shared_ptr<Accessory>(new Accessory(
		Item(engine::raritySystem.getAccessoryMod(rarityType),
		GameObject(
		accessoryTemplate.name,
		GameObject::ACCESSORY, 
		accessoryTemplate.glyph),
		accessoryTemplate.weightKg),
		spellPower
		));

	//rarity color
	accessory->glyph.fgColor = accessory->glyph.fgColor * rarityType.color;

	return accessory;
}

std::shared_ptr<Consumable> ObjectFactory::createConsumable(TemplateConsumable &consumableTemplate, RarityType &rarityType){
	double potency =
		engine::consumablePotencyMax *
		consumableTemplate.potencyFromMax *
		rarityType.improvementMultiplier *
		engine::random.variationMultiplier(engine::statisticVariation);

	double concentration =
		engine::consumableConcentrationMax *
		consumableTemplate.concentrationFromMax *
		rarityType.improvementMultiplier *
		engine::random.variationMultiplier(engine::statisticVariation);

	std::shared_ptr<Consumable> consumable = std::shared_ptr<Consumable>(new Consumable(
		Item(engine::raritySystem.getConsumableMod(rarityType),
		GameObject(
		consumableTemplate.name,
		GameObject::CONSUMABLE,
		consumableTemplate.glyph),
		consumableTemplate.weightKg),
		potency,
		concentration
		));

	//rarity color
	consumable->glyph.fgColor = consumable->glyph.fgColor * rarityType.color;

	return consumable;
}

std::shared_ptr<Weapon> ObjectFactory::createRandomWeapon(RarityType &rarityType){
	int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.weaponTemplates.size() - 1);
	auto &hashmapIterator = engine::objectLibrary.weaponTemplates.begin();
	std::advance(hashmapIterator, randomIndex);
	TemplateWeapon &randomTemplate = hashmapIterator->second;
	return engine::objectFactory.createWeapon(randomTemplate, rarityType);
}

std::shared_ptr<Armor> ObjectFactory::createRandomArmor(RarityType &rarityType){
	int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.armorTemplates.size() - 1);
	auto &hashmapIterator = engine::objectLibrary.armorTemplates.begin();
	std::advance(hashmapIterator, randomIndex);
	TemplateArmor &randomTemplate = hashmapIterator->second;
	return engine::objectFactory.createArmor(randomTemplate, rarityType);
}

std::shared_ptr<Accessory> ObjectFactory::createRandomAccessory(RarityType &rarityType){
	int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.accessoryTemplates.size() - 1);
	auto &hashmapIterator = engine::objectLibrary.accessoryTemplates.begin();
	std::advance(hashmapIterator, randomIndex);
	TemplateAccessory &randomTemplate = hashmapIterator->second;
	return engine::objectFactory.createAccessory(randomTemplate, rarityType);
}

std::shared_ptr<Consumable> ObjectFactory::createRandomConsumable(RarityType &rarityType){
	int randomIndex = engine::random.generator->getInt(0, engine::objectLibrary.consumableTemplates.size() - 1);
	auto &hashmapIterator = engine::objectLibrary.consumableTemplates.begin();
	std::advance(hashmapIterator, randomIndex);
	TemplateConsumable &randomTemplate = hashmapIterator->second;
	return createConsumable(randomTemplate, rarityType);
}

void ObjectFactory::generateLootDrop(Creature &creature){
	std::vector<std::shared_ptr<Item>> lootItems;
	for (int dropNumber = engine::lootDropRolls; dropNumber > 0; --dropNumber){
		if (engine::random.chance(engine::lootRollDropChance)){
			int type = engine::random.generator->getInt(0, 3);
			RarityType &rarityType = *engine::raritySystem.getRarityType(engine::raritySystem.getRarityRoll(&creature));
			//armor
			if (type == 0){
				lootItems.push_back(createRandomArmor(rarityType));
			}
			//weapon
			else if (type == 1){
				lootItems.push_back(createRandomWeapon(rarityType));
			}
			//accessory
			else if (type == 2){
				lootItems.push_back(createRandomAccessory(rarityType));
			}
			//consumable
			else if (type == 3){
				lootItems.push_back(createRandomConsumable(rarityType));
			}
		}
	}
	for (auto &lootItem : lootItems){
		engine::areaHandler.getCurrentArea()->placeItem(lootItem, creature.location);
	}
}