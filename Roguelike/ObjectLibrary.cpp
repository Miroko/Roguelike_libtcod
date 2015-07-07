#include "ObjectLibrary.h"
#include "EffectHealth.h"
#include "EffectIncreasedDamage.h"
#include "EffectIncreasedDefence.h"
#include "Armor.h"
#include "Weapon.h"
#include "AiMonster.h"
#include "AiNone.h"
#include "AiVillager.h"

bool ObjectLibrary::addTile(std::string id, std::unique_ptr<Tile> tile){
	auto& inserted = tiles.insert(std::pair<std::string, std::unique_ptr<Tile>>(id, std::move(tile)));
	return inserted.second;
}
bool ObjectLibrary::addDoor(std::string id, Door door){
	auto& inserted = doors.insert(std::pair<std::string, Door>(id, door));
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
bool ObjectLibrary::addCreatureAi(std::string id, std::unique_ptr<CreatureAi> ai){
	auto& inserted = creatureAIs.insert(std::pair<std::string, std::unique_ptr<CreatureAi>>(id, std::move(ai)));
	return inserted.second;
}
bool ObjectLibrary::addCreatureTemplate(TemplateCreature creatureTemplate){
	auto& inserted = creatureTemplates.insert(std::pair<std::string, TemplateCreature>(creatureTemplate.id, creatureTemplate));
	return inserted.second;
}
bool ObjectLibrary::addCreaturePresetTemplate(TemplateCreaturePreset creaturePresetTemplate){
	auto& inserted = creaturePresetTemplates.insert(std::pair<std::string, TemplateCreaturePreset>(creaturePresetTemplate.id, creaturePresetTemplate));
	return inserted.second;
}
Tile *ObjectLibrary::getTile(std::string id){
	auto &retrieved = tiles.find(id);
	return retrieved->second.get();
}
Door *ObjectLibrary::getDoor(std::string id){
	auto &retrieved = doors.find(id);
	return &retrieved->second;
}
TemplateWeapon *ObjectLibrary::getTemplateWeapon(std::string id){
	auto &retrieved = weaponTemplates.find(id);
	return &retrieved->second;
}
TemplateArmor *ObjectLibrary::getTemplateArmor(std::string id){
	auto &retrieved = armorTemplates.find(id);
	return &retrieved->second;
}
CreatureAi *ObjectLibrary::getAi(std::string id){
	auto &retrieved = creatureAIs.find(id);
	return retrieved->second.get();
}
TemplateCreature *ObjectLibrary::getTemplateCreature(std::string id){
	auto &retrieved = creatureTemplates.find(id);
	return &retrieved->second;
}
TemplateCreaturePreset *ObjectLibrary::getTemplateCreaturePreset(std::string id){
	auto &retrieved = creaturePresetTemplates.find(id);
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

	//Creatures
	addCreatureTemplate(TemplateCreature(
		"creature_human",
		"Human",
		Glyph('h', TCODColor::lighterAmber),
		{
			CreatureLimb("Head", 0.2f, Armor::ARMOR_HEAD),
			CreatureLimb("Body", 0.5f, Armor::ARMOR_BODY),
			CreatureLimb("Arm", 0.3f, Armor::ARMOR_HAND),
			CreatureLimb("Leg", 0.3f, Armor::ARMOR_LEG)
		}));
	addCreatureTemplate(TemplateCreature(
		"creature_child",
		"Child",
		Glyph('c', TCODColor::lighterAmber),
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

	//AIs
	addCreatureAi(
		"ai_none",
		std::unique_ptr<CreatureAi>(new AiNone()));
	addCreatureAi(
		"ai_monster",
		std::unique_ptr<CreatureAi>(new AiMonster()));
	addCreatureAi(
		"ai_villager",
		std::unique_ptr<CreatureAi>(new AiVillager()));

	//Player
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"player",
		"creature_human",
		"ai_none",
		"Player",
		0.20f,
		{ "weapon_sword" },
		{ "armor_body_leather" }));
	//Creature presets
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"human_man_villager",
		"creature_human",
		"ai_villager",
		"Man",
		0.10f,
		{ "weapon_dagger" },
		{ "armor_body_leather" }));
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"human_woman_villager",
		"creature_human",
		"ai_villager",
		"Woman",
		0.10f,
		{ "weapon_dagger" },
		{ "armor_body_leather" }));
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"human_child_villager",
		"creature_child",
		"ai_villager",
		"Child",
		0.03f,
		{ /*none*/ },
		{ /*none*/ }));
	addCreaturePresetTemplate(TemplateCreaturePreset(
		"goblin_dagger",
		"creature_goblin",
		"ai_monster",
		"Goblin",
		0.05f,
		{ "weapon_dagger" },
		{ "armor_body_leather" }));

	//Doors
	addDoor(
		"door_wooden",
		Door("Wooden door",
		Glyph(TCODColor::darkSepia, TCODColor::darkerSepia, 'D'),
		Glyph(TCODColor::darkerSepia, TCODColor::darkSepia, 'D')));

	//tiles + portals
	addTile("forest_wall", std::make_unique<Tile>(Tile("Tree", Tile::WALL, Glyph(TCODColor::darkerChartreuse, TCODColor(5, 20, 5), TCOD_CHAR_SPADE), false, 0.0f)));
	addTile("forest_floor", std::make_unique<Tile>(Tile("Land", Tile::FLOOR, Glyph(TCODColor(5, 20, 5), TCODColor(5, 20, 5)), true, 10.0f)));
	addTile("forest_portal", std::make_unique<Tile>(Tile("Exit", Tile::PORTAL, Glyph(TCODColor::darkChartreuse, TCODColor(5, 20, 5), '>'), true, 10.0f)));

	addTile("stone_wall", std::make_unique<Tile>(Tile("Stone", Tile::WALL, Glyph(TCODColor::darkerGrey, TCODColor::darkerGrey), false, 0.0f)));
	addTile("stone_floor", std::make_unique<Tile>(Tile("Stone floor", Tile::FLOOR, Glyph(TCODColor::darkestGrey, TCODColor::darkestGrey), true, 10.0f)));

	addTile("wood_wall", std::make_unique<Tile>(Tile("Wooden wall", Tile::WALL, Glyph(TCODColor::darkSepia, TCODColor::darkSepia), false, 0.0f)));
	addTile("wood_floor", std::make_unique<Tile>(Tile("Wooden floor", Tile::FLOOR, Glyph(TCODColor::darkerSepia, TCODColor::darkerSepia), true, 10.0f)));

	addTile("sand_path", std::make_unique<Tile>(Tile("Sand path", Tile::FLOOR, Glyph(TCODColor::darkestSepia, TCODColor::darkestSepia), true, 7.0f)));

	//Rarity types
	addRarity(RarityType(
		"rarity_common",
		"Common",
		1.00f, 0.30f, 1,
		TCODColor::lightestCyan,
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
