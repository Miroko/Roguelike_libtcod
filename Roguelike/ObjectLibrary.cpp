#include "ObjectLibrary.h"
#include "Portal.h"
#include "EffectHealth.h"
#include "EffectIncreasedDamage.h"
#include "EffectIncreasedDefence.h"
#include "Armor.h"
#include "Weapon.h"

bool ObjectLibrary::addTile(std::string id, std::unique_ptr<Tile> tile){
	auto& inserted = tiles.insert(std::pair<std::string, std::unique_ptr<Tile>>(id, std::move(tile)));
	return inserted.second;
}
bool ObjectLibrary::addCreatureTemplate(TemplateCreature creatureTemplate){
	auto& inserted = creatureTemplates.insert(std::pair<std::string, TemplateCreature>(creatureTemplate.id, creatureTemplate));
	return inserted.second;
}
bool ObjectLibrary::addWeaponTemplate(TemplateWeapon weaponTemplate){
	auto& inserted = weaponTemplates.insert(std::pair<std::string, TemplateWeapon>(weaponTemplate.id, weaponTemplate));
	return inserted.second;
}
bool ObjectLibrary::addArmorTemplate(TemplateArmor armorTemplate){
	auto& inserted = armorTemplates.insert(std::pair<std::string, TemplateArmor>(armorTemplate.id, armorTemplate));
	return inserted.second;
}
void ObjectLibrary::addRarity(RarityType rarity){
	rarityTypes.push_back(rarity);
}
bool ObjectLibrary::addCreaturePresetTemplate(TemplateCreaturePreset creaturePresetTemplate){
	auto& inserted = creaturePresetTemplates.insert(std::pair<std::string, TemplateCreaturePreset>(creaturePresetTemplate.id, creaturePresetTemplate));
	return inserted.second;
}
Tile *ObjectLibrary::getTile(std::string id){
	auto &retrieved = tiles.find(id);
	return retrieved->second.get();
}
TemplateWeapon *ObjectLibrary::getTemplateWeapon(std::string id){
	auto &retrieved = weaponTemplates.find(id);
	return &retrieved->second;
}
TemplateArmor *ObjectLibrary::getTemplateArmor(std::string id){
	auto &retrieved = armorTemplates.find(id);
	return &retrieved->second;
}
TemplateCreature *ObjectLibrary::getTemplateCreature(std::string id){
	auto &retrieved = creatureTemplates.find(id);
	return &retrieved->second;
}
RarityType *ObjectLibrary::getRarity(std::string id){
	for (RarityType &rarity : rarityTypes){
		if (rarity.id == id) return &rarity;
	}
	return nullptr;
}
RarityType *ObjectLibrary::getRarity(float roll){
	for (RarityType &rarity : rarityTypes){
		if (roll < rarity.prevalence) return &rarity;
	}
	return nullptr;
}
TemplateCreaturePreset *ObjectLibrary::getTemplateCreaturePreset(std::string id){
	auto &retrieved = creaturePresetTemplates.find(id);
	return &retrieved->second;
}

void ObjectLibrary::sortRarityTypes(){
	rarityTypes.sort([](const RarityType &a, const RarityType &b){
		return a.prevalence < b.prevalence;
	});
}

void ObjectLibrary::init(){
	maxWeight = 50.0f;
	maxHealth = 1000.0f;
	maxDamage = maxHealth / 3.0f;
	maxDefence = maxDamage / 2;
	headDefence = 0.3f;
	bodyDefence = 0.4f;
	handDefence = 0.1f;
	legDefence = 0.2f;
	rangedMultiplier = 0.3f;

	//Creatures
	addCreatureTemplate(TemplateCreature(
		"creature_human_man",
		"Man",
		Glyph('h', TCODColor::lighterAmber),
		{
			CreatureLimb("Head", 0.2f, Armor::ARMOR_HEAD),
			CreatureLimb("Body", 0.5f, Armor::ARMOR_BODY),
			CreatureLimb("Arm", 0.3f, Armor::ARMOR_HAND),
			CreatureLimb("Leg", 0.3f, Armor::ARMOR_LEG)
		}));
	addCreatureTemplate(TemplateCreature(
		"creature_goblin",
		"Goblin",
		Glyph('g', TCODColor::lighterChartreuse),
		{
			CreatureLimb("Head", 0.3f, Armor::ARMOR_HEAD),
			CreatureLimb("Body", 0.5f, Armor::ARMOR_BODY),
			CreatureLimb("Arm", 0.3f, Armor::ARMOR_HAND),
			CreatureLimb("Leg", 0.2f, Armor::ARMOR_LEG)
		}));
	
	//Weapons
	addWeaponTemplate(TemplateWeapon(
		"weapon_sword",
		"Sword",
		Glyph('s', TCODColor::lightGrey),
		0.20f, 0.10f,
		Weapon::WEAPON_MELEE));
	addWeaponTemplate(TemplateWeapon(
		"weapon_dagger",
		"Dagger",
		Glyph('d', TCODColor::lightGrey),
		0.05f, 0.02f,
		Weapon::WEAPON_MELEE));

	//Armors
	addArmorTemplate(TemplateArmor(
		"armor_body_leather",
		"Leather body armor",
		Glyph('B', TCODColor::lightGrey),
		0.10f, 0.05f,
		Armor::ARMOR_BODY));

	//Creature presets
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"human_man_sword",
		"creature_human_man",
		0.20f,
		{
			"weapon_sword"
		},
		{
			"armor_body_leather"
		}
		));
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"goblin_dagger",
		"creature_goblin",
		0.05f,
		{
			"weapon_dagger"
		},
		{
			"armor_body_leather"
		}
		));

	//tiles + portals
	addTile("forest_wall", std::make_unique<Tile>(Tile("Tree", GameObject::WALL, Glyph(TCODColor::darkerChartreuse, TCODColor(5, 20, 5), TCOD_CHAR_SPADE))));
	addTile("forest_floor", std::make_unique<Tile>(Tile("Land", GameObject::FLOOR, Glyph(TCODColor(5, 20, 5), TCODColor(5, 20, 5)))));
	addTile("forest_portal", std::make_unique<Portal>(Portal("Exit", Glyph(TCODColor::darkChartreuse, TCODColor(5, 20, 5), '>'))));

	addTile("stone_wall", std::make_unique<Tile>(Tile("Stone", GameObject::WALL, Glyph(TCODColor::darkerGrey, TCODColor::darkerGrey))));
	addTile("stone_floor", std::make_unique<Tile>(Tile("Stone floor", GameObject::FLOOR, Glyph(TCODColor::darkestGrey, TCODColor::darkestGrey))));

	addTile("wood_wall", std::make_unique<Tile>(Tile("Wooden wall", GameObject::WALL, Glyph(TCODColor::darkerSepia, TCODColor::darkerSepia))));
	addTile("wood_floor", std::make_unique<Tile>(Tile("Wooden floor", GameObject::FLOOR, Glyph(TCODColor::darkestSepia, TCODColor::darkestSepia))));

	//Rarity types
	addRarity(RarityType(
		"rarity_common",
		"Common",
		1.00f, 0.05f, 1,
		TCODColor::lighterCyan,
		{
			RarityModCreature("Weak", { std::shared_ptr<CreatureEffect>(new EffectHealth(0.7f)) }),
			RarityModCreature("Injured", { std::shared_ptr<CreatureEffect>(new EffectHealth(0.5f)) })
		},
		{
			RarityModWeapon("Rusty", { std::shared_ptr<WeaponEffect>(new EffectIncreasedDamage(0.7f)) }),
			RarityModWeapon("Broken", { std::shared_ptr<WeaponEffect>(new EffectIncreasedDamage(0.5f)) })
		},
		{
			RarityModArmor("Worn", { std::shared_ptr<ArmorEffect>(new EffectIncreasedDefence(0.7f)) }),
			RarityModArmor("Damaged", { std::shared_ptr<ArmorEffect>(new EffectIncreasedDefence(0.5f)) })
		}));
	addRarity(RarityType(
		"rarity_uncommon",
		"Uncommon",
		0.40f, 0.10f, 2,
		TCODColor::lighterBlue,
		{
			RarityModCreature("Tough", { std::shared_ptr<CreatureEffect>(new EffectHealth(1.5f)) }),
			RarityModCreature("Angry", { std::shared_ptr<CreatureEffect>(new EffectHealth(1.2f)) })
		},
		{
			RarityModWeapon("New", { std::shared_ptr<WeaponEffect>(new EffectIncreasedDamage(1.5f)) }),
			RarityModWeapon("Good grip", { std::shared_ptr<WeaponEffect>(new EffectIncreasedDamage(1.2f)) })
		},
		{
			RarityModArmor("Protective", { std::shared_ptr<ArmorEffect>(new EffectIncreasedDefence(1.5f)) }),
			RarityModArmor("Fitting", { std::shared_ptr<ArmorEffect>(new EffectIncreasedDefence(1.2f)) })
		}));
	sortRarityTypes();
}
