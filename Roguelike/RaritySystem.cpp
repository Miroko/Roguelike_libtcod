#include "RaritySystem.h"
#include "ItemAffixWeight.h"
#include "EquipmentAffixDurability.h"
#include "ArmorAffixDefence.h"
#include "WeaponAffixDamage.h"
#include "WeaponAffixAccuracy.h"
#include "WeaponAffixStamina.h"
#include "ConsumableAffixHealthRegenerate.h"
#include "ConsumableAffixStaminaRegenerate.h"
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
	double rarityFromCreature = 0;
	if (fromCreature != nullptr){
		rarityFromCreature = 
			engine::random.generator->getDouble(0, (1.0 - fromCreature->rarityType->prevalence)) *
			engine::lootRarityFromCreatureRarityRatio;
	}
	double rarityRoll = engine::random.generator->getDouble(rarityFromCreature, 1.0);
	return rarityRoll;
}

void RaritySystem::init(){
	rarityTypes = std::vector<RarityType>{
		RarityType("common", "Common", TCODColor(TCODColor::grey), 1.0, 1.0),
		RarityType("uncommon", "Uncommon", TCODColor(TCODColor::azure), 0.20, 1.5),
		RarityType("rare", "Rare", TCODColor(TCODColor::violet), 0.05, 2.5),
		RarityType("epic", "Epic", TCODColor(TCODColor::green), 0.005, 3.5),
		RarityType("unique", "Unique", TCODColor(TCODColor::orange), 0.0005, 5.5)
	};
	std::sort(rarityTypes.begin(), rarityTypes.end(),
		[](RarityType &a, RarityType &b){
		return a.prevalence <= b.prevalence;
	});
	for (auto &rarityType : rarityTypes){
		//Pre
		//armor affixes
		rarityType.armorAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ArmorAffixDefence("Defensive", 0.3 * rarityType.improvementMultiplier)
			));
		rarityType.armorAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ItemAffixWeight("Light", -0.3 * rarityType.improvementMultiplier)
			));
		//weapon affixes
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
		//consumable affixes
		rarityType.consumableAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixHealthRegenerate("Healing",(int)(4 * rarityType.improvementMultiplier), 0.03 * rarityType.improvementMultiplier)
			));
		rarityType.consumableAffixesPre.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixStaminaRegenerate("Refreshing", (int)(4 * rarityType.improvementMultiplier), 0.03 * rarityType.improvementMultiplier)
			));

		//Post
		//armor affixes
		rarityType.armorAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ArmorAffixDefence("Protection", 0.6 * rarityType.improvementMultiplier)
			));
		//weapon affixes
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
		//consumable affixes
		rarityType.consumableAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixHealthRegenerate("Restoration", (int)(8 * rarityType.improvementMultiplier), 0.04 * rarityType.improvementMultiplier)
			));
		rarityType.consumableAffixesPost.push_back(
			std::shared_ptr<RarityAffix>(
			new ConsumableAffixStaminaRegenerate("Enduration", (int)(8 * rarityType.improvementMultiplier), 0.04 * rarityType.improvementMultiplier)
			));
	}
}
