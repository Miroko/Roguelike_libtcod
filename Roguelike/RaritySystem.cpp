#include "RaritySystem.h"
#include "ItemAffixWeight.h"
#include "EquipmentAffixDurability.h"
#include "ArmorAffixDefence.h"
#include "WeaponAffixDamage.h"
#include "WeaponAffixAccuracy.h"
#include "WeaponAffixStamina.h"
#include "AccessoryAffixMagic.h"
#include "AccessoryAffixSkill.h"
#include "AccessoryAffixSpellPower.h"
#include "ConsumableAffixHealth.h"
#include "ConsumableAffixStamina.h"
#include "ConsumableAffixMagic.h"
#include "Engine.h"
#include <algorithm>

RarityMod RaritySystem::getCreatureMod(RarityType &rarityType){
	std::vector<RarityAffix*> affixes;
	affixes.push_back(rarityType.creatureAffixesPre.at(engine::random.generator->getInt(0, rarityType.creatureAffixesPre.size() - 1)).get());
	affixes.push_back(rarityType.creatureAffixesPost.at(engine::random.generator->getInt(0, rarityType.creatureAffixesPost.size() - 1)).get());
	return RarityMod(rarityType, affixes);
}

RarityMod RaritySystem::getArmorMod(RarityType &rarityType){
	std::vector<RarityAffix*> affixes;
	affixes.push_back(rarityType.armorAffixesPre.at(engine::random.generator->getInt(0, rarityType.armorAffixesPre.size() - 1)).get());
	affixes.push_back(rarityType.armorAffixesPost.at(engine::random.generator->getInt(0, rarityType.armorAffixesPost.size() - 1)).get());
	return RarityMod(rarityType, affixes);
}

RarityMod RaritySystem::getWeaponMod(RarityType &rarityType){
	std::vector<RarityAffix*> affixes;
	affixes.push_back(rarityType.weaponAffixesPre.at(engine::random.generator->getInt(0, rarityType.weaponAffixesPre.size() - 1)).get());
	affixes.push_back(rarityType.weaponAffixesPost.at(engine::random.generator->getInt(0, rarityType.weaponAffixesPost.size() - 1)).get());
	return RarityMod(rarityType, affixes);
}

RarityMod RaritySystem::getAccessoryMod(RarityType &rarityType){
	std::vector<RarityAffix*> affixes;
	affixes.push_back(rarityType.accessoryAffixesPre.at(engine::random.generator->getInt(0, rarityType.accessoryAffixesPre.size() - 1)).get());
	affixes.push_back(rarityType.accessoryAffixesPost.at(engine::random.generator->getInt(0, rarityType.accessoryAffixesPost.size() - 1)).get());
	return RarityMod(rarityType, affixes);
}

RarityMod RaritySystem::getConsumableMod(RarityType &rarityType){
	std::vector<RarityAffix*> affixes;
	affixes.push_back(rarityType.consumableAffixesPre.at(engine::random.generator->getInt(0, rarityType.consumableAffixesPre.size() - 1)).get());
	affixes.push_back(rarityType.consumableAffixesPost.at(engine::random.generator->getInt(0, rarityType.consumableAffixesPost.size() - 1)).get());
	return RarityMod(rarityType, affixes);
}

RarityType* RaritySystem::getRarityType(double rarityRoll){
	for (auto &rarityType : rarityTypes){
		if (rarityRoll <= rarityType.prevalence){
			return &rarityType;
		}
	}	
	return nullptr;
}

RarityType* RaritySystem::getRarityType(std::string id){
	for (auto &rarityType : rarityTypes){
		if (rarityType.id == id){
			return &rarityType;
		}
	}
	return nullptr;
}

double RaritySystem::getRarityRoll(Creature *fromCreature){
	if (fromCreature != nullptr){
		double prevalenceMin =
			engine::random.generator->getDouble(
			0.0,
			1.0);
		prevalenceMin *= engine::lootMinPrevalenceMultiplier;
		return
			engine::random.generator->getDouble(
			prevalenceMin,
			std::min(prevalenceMin + fromCreature->rarityType->prevalence, 1.0));
	}
	else{
		return 
			engine::random.generator->getDouble(
			0.0,
			1.0);
	}
}

void RaritySystem::init(){
	rarityTypes = std::vector<RarityType>{
		RarityType("common", "Common", TCODColor(TCODColor::grey), 1.0, 1.0),
		RarityType("uncommon", "Uncommon", TCODColor(TCODColor::azure), 0.20, 1.5),
		RarityType("rare", "Rare", TCODColor(TCODColor::violet), 0.05, 2.0),
		RarityType("epic", "Epic", TCODColor(TCODColor::green), 0.01, 2.6),
		RarityType("unique", "Unique", TCODColor(TCODColor::orange), 0.005, 3.3)
	};
	std::sort(rarityTypes.begin(), rarityTypes.end(),
		[](RarityType &a, RarityType &b){
		return a.prevalence <= b.prevalence;
	});
	for (auto &rarityType : rarityTypes){
		//Pre
		//armor
		rarityType.armorAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ArmorAffixDefence("Defensive", 0.3 * rarityType.improvementMultiplier)
			));
		rarityType.armorAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ItemAffixWeight("Light", -0.3 * rarityType.improvementMultiplier)
			));
		//weapon
		rarityType.weaponAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new WeaponAffixDamage("Damaging", 0.3 * rarityType.improvementMultiplier)
			));
		rarityType.weaponAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new WeaponAffixAccuracy("Accurate", 0.03 * rarityType.improvementMultiplier)
			));
		rarityType.weaponAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new WeaponAffixStamina("Swift", -0.03 * rarityType.improvementMultiplier)
			));
		rarityType.weaponAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ItemAffixWeight("Heavy", 0.3 * rarityType.improvementMultiplier)
			));
		rarityType.weaponAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ItemAffixWeight("Light", -0.3 * rarityType.improvementMultiplier)
			));
		//accessory
		rarityType.accessoryAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixMagic("Mystical", 0.2 * rarityType.improvementMultiplier)
			));
		rarityType.accessoryAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixSpellPower("Empowering", 0.2 * rarityType.improvementMultiplier)
			));
		rarityType.accessoryAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixSkill("Burning", 0.2 * rarityType.improvementMultiplier, *engine::objectLibrary.creatureSkills["skill_fire"])
			));
		rarityType.accessoryAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixSkill("Freezing", 0.2 * rarityType.improvementMultiplier, *engine::objectLibrary.creatureSkills["skill_frost"])
			));
		rarityType.accessoryAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixSkill("Restoring", 0.2 * rarityType.improvementMultiplier, *engine::objectLibrary.creatureSkills["skill_restoration"])
			));
		//consumable
		rarityType.consumableAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixHealth("Healing", 0.04 * rarityType.improvementMultiplier, 0.5 * rarityType.improvementMultiplier)
			));
		rarityType.consumableAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixStamina("Refreshing", 0.04 * rarityType.improvementMultiplier, 0.5 * rarityType.improvementMultiplier)
			));
		rarityType.consumableAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixMagic("Magical", 0.04 * rarityType.improvementMultiplier, 0.5 * rarityType.improvementMultiplier)
			));

		//Post
		//armor
		rarityType.armorAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ArmorAffixDefence("Protection", 0.6 * rarityType.improvementMultiplier)
			));
		//weapon
		rarityType.weaponAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new WeaponAffixDamage("Destruction", 0.6 * rarityType.improvementMultiplier)
			));
		rarityType.weaponAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new WeaponAffixAccuracy("Certainty", 0.06 * rarityType.improvementMultiplier)
			));
		rarityType.weaponAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new WeaponAffixStamina("Agility", -0.06 * rarityType.improvementMultiplier)
			));
		//accessory
		rarityType.accessoryAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixMagic("Conjuring", 0.4 * rarityType.improvementMultiplier)
			));
		rarityType.accessoryAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new AccessoryAffixSpellPower("Sorcery", 0.4 * rarityType.improvementMultiplier)
			));
		//consumable
		rarityType.consumableAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixHealth("Restoration", 0.03 * rarityType.improvementMultiplier, 0.8 * rarityType.improvementMultiplier)
			));
		rarityType.consumableAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixStamina("Enduration", 0.03 * rarityType.improvementMultiplier, 0.8 * rarityType.improvementMultiplier)
			));
		rarityType.consumableAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixMagic("Occultism", 0.03 * rarityType.improvementMultiplier, 0.8 * rarityType.improvementMultiplier)
			));
	}
}
