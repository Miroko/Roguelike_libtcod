#include "ObjectLibrary.h"
#include "AiVillager.h"
#include "AiAlchemist.h"
#include "AiBlacksmith.h"
#include "AiMonster.h"
#include "AiNone.h"
#include "Door.h"
#include "Bed.h"
#include "Forge.h"
#include "Anvil.h"
#include "AlchemyTable.h"
#include "Wall.h"
#include "Floor.h"
#include "Water.h"
#include "Portal.h"
#include "CreatureEffectHealth.h"
#include "CreatureEffectMagic.h"
#include "CreatureEffectStamina.h"
#include "WeaponAction.h"
#include "MagicAction.h"

void ObjectLibrary::init(){
	tiles = std::unordered_map<std::string, std::shared_ptr<Tile>>{
		{ "house_wall_wood", std::shared_ptr<Tile>(new Wall("Wooden house wall", Glyph(TCODColor::darkerSepia))) },
		{ "house_wall_stone", std::shared_ptr<Tile>(new Wall("Stone house wall", Glyph(TCODColor(50, 50, 50)))) },
		{ "house_floor_wood", std::shared_ptr<Tile>(new Floor("Wooden house floor", Glyph(TCODColor::darkestSepia))) },
		{ "path_sand", std::shared_ptr<Tile>(new Floor("Sand path", Glyph(TCODColor(14, 11, 6)), 5.0f)) },
		{ "forest_wall_tree", std::shared_ptr<Tile>(new Wall("Tree", Glyph(TCODColor(5, 20, 5), TCODColor::darkerChartreuse, TCOD_CHAR_SPADE))) },
		{ "forest_floor_grass", std::shared_ptr<Tile>(new Floor("Land", Glyph(TCODColor(5, 20, 5)))) },
		{ "forest_floor_stone", std::shared_ptr<Tile>(new Floor("Stone floor", Glyph(TCODColor(30, 30, 30)))) },
		{ "forest_wall_stone", std::shared_ptr<Tile>(new Wall("Stone", Glyph(TCODColor(45, 45, 45)))) },
		{ "forest_portal", std::shared_ptr<Tile>(new Portal("Exit", Glyph(TCODColor(0, 10, 0), TCODColor::darkerChartreuse, '>'))) },
		{ "cave_wall_wood", std::shared_ptr<Tile>(new Wall("Wooden column", Glyph(TCODColor::darkerSepia))) },
		{ "cave_wall_stone1", std::shared_ptr<Tile>(new Wall("Cave wall", Glyph(TCODColor::grey))) },
		{ "cave_wall_stone2", std::shared_ptr<Tile>(new Wall("Cave wall", Glyph(TCODColor::darkGrey))) },
		{ "cave_floor_stone1", std::shared_ptr<Tile>(new Floor("Cave floor", Glyph(TCODColor(45, 45, 45)))) },
		{ "cave_floor_stone2", std::shared_ptr<Tile>(new Floor("Cave floor", Glyph(TCODColor::darkestGrey))) },
		{ "cave_portal", std::shared_ptr<Tile>(new Portal("Tunnel", Glyph(TCODColor::darkestGrey, TCODColor(55, 55, 55), '>'))) },
		{ "cave_water", std::shared_ptr<Tile>(new Water("Water", Glyph(TCODColor::darkestBlue))) }
	};
	operatables = std::unordered_map<std::string, std::shared_ptr<OperatableObject>>{
		{ "door_wood", std::shared_ptr<OperatableObject>(new Door(
			"Wooden door",
			Glyph(TCODColor::darkestSepia, TCODColor::darkerSepia, 'D'),
			Glyph(TCODColor::darkerSepia, TCODColor::darkestSepia, 'D'),
			100)) },
		{ "bed_wood", std::shared_ptr<OperatableObject>(new Bed(
			"Wooden bed",
			Glyph(TCODColor::darkerSepia, TCODColor::darkSepia, 'B'),
			100)) },
		{ "forge", std::shared_ptr<OperatableObject>(new Forge()) },
		{ "anvil", std::shared_ptr<OperatableObject>(new Anvil()) },
		{ "alchemy_table1", std::shared_ptr<OperatableObject>(new AlchemyTable(
			"Alchemy table",
			Glyph(TCODColor::darkSepia, TCODColor::lightViolet, '%'))) },
		{ "alchemy_table2", std::shared_ptr<OperatableObject>(new AlchemyTable(
			"Alchemy table",
			Glyph(TCODColor::darkSepia, TCODColor::lightSea, '%'))) }
	};
	ais = std::unordered_map<std::string, std::shared_ptr<CreatureAi>>{
		{ "ai_villager", std::shared_ptr<CreatureAi>(new AiVillager()) },
		{ "ai_alchemist", std::shared_ptr<CreatureAi>(new AiAlchemist()) },
		{ "ai_blacksmith", std::shared_ptr<CreatureAi>(new AiBlacksmith()) },
		{ "ai_monster", std::shared_ptr<CreatureAi>(new AiMonster()) },
		{ "ai_none", std::shared_ptr<CreatureAi>(new AiNone()) }
	};
	creatureAction = std::unordered_map<std::string, std::shared_ptr<CreatureAction>>{
		//weapon
		{ "strike", std::shared_ptr<CreatureAction>(new WeaponAction("Basic strike", "Strikes", 1.00, 1, 0.10, 0.10, 0.00, 0.00)) },
		{ "stab", std::shared_ptr<CreatureAction>(new WeaponAction("Basic stab", "Stabs", 0.70, 1, 0.50, -0.50, 0.00, 0.00)) },
		{ "slash", std::shared_ptr<CreatureAction>(new WeaponAction("Basic slash", "Slashes", 0.80, 1, 0.00, 0.50, 0.30, 0.00)) },
		{ "swing", std::shared_ptr<CreatureAction>(new WeaponAction("Basic swing", "Swings", 0.90, 1, 0.30, 0.80, 0.30, 0.20)) },
		{ "smash", std::shared_ptr<CreatureAction>(new WeaponAction("Basic smash", "Smashes", 0.70, 1, 0.70, -0.70, 0.30, 0.80)) },
		{ "shot", std::shared_ptr<CreatureAction>(new WeaponAction("Basic shot", "Shoots", 0.80, 8, 0.00, -0.10, 0.10, 0.10)) },
		//magic
		{ "fireball", std::shared_ptr<CreatureAction>(new MagicAction("Fireball", "Fireball", 0.70, 6, 0.20, 0.05,
		{ std::shared_ptr<CreatureEffect>(new CreatureEffectHealth("Burn", -0.02, 0.20)),
		  std::shared_ptr<CreatureEffect>(new CreatureEffectStamina("Heat", -0.03, 0.20)) })) }
	};
	creatureSkills = std::unordered_map<std::string, std::shared_ptr<CreatureSkill>>{
		//weapon
		{ "skill_sword", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::WEAPON, "Sword Skill",
		{ creatureAction["strike"], creatureAction["stab"], creatureAction["slash"] }))},
		{ "skill_dagger", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::WEAPON, "Dagger Skill",
		{ creatureAction["stab"], creatureAction["slash"] })) },
		{ "skill_staff", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::WEAPON, "Staff Skill",
		{ creatureAction["strike"], creatureAction["swing"], creatureAction["smash"] })) },
		{ "skill_mace", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::WEAPON, "Mace Skill",
		{ creatureAction["strike"], creatureAction["smash"] })) },
		{ "skill_bow", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::WEAPON, "Bow Skill",
		{ creatureAction["shot"] })) },
		//magic
		{ "skill_fire", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::MAGIC, "Fire Magic",
		{ creatureAction["fireball"] } )) }
	};
	creatureBaseTemplates = std::unordered_map<std::string, TemplateCreatureBase>{
		{ "humanoid", TemplateCreatureBase({
			CreatureLimb("Head", 0.4f, GameObject::ARMOR_HEAD, 2),
			CreatureLimb("Body", 0.8f, GameObject::ARMOR_BODY, 0),
			CreatureLimb("Left arm", 0.7f, GameObject::ARMOR_HAND, 3, true),
			CreatureLimb("Right arm", 0.7f, GameObject::ARMOR_HAND, 3, true),
			CreatureLimb("Left leg", 0.6f, GameObject::ARMOR_LEG, 1),
			CreatureLimb("Right leg", 0.6f, GameObject::ARMOR_LEG, 1)
		}) },
		{ "giant", TemplateCreatureBase({
			CreatureLimb("Head", 0.9f, GameObject::ARMOR_HEAD, 2),
			CreatureLimb("Body", 1.0f, GameObject::ARMOR_BODY, 0),
			CreatureLimb("Left arm", 0.9f, GameObject::ARMOR_HAND, 1, true),
			CreatureLimb("Right arm", 0.9f, GameObject::ARMOR_HAND, 1, true),
			CreatureLimb("Left leg", 1.0f, GameObject::ARMOR_LEG, 0),
			CreatureLimb("Right leg", 1.0f, GameObject::ARMOR_LEG, 0)
		}) }
	};
	creaturePresetTemplates = std::unordered_map<std::string, TemplateCreaturePreset>{
		{ "player", TemplateCreaturePreset(
			"player",
			"Player",
			Glyph('@', TCODColor::lightAmber),
			0.8,
			0.6,
			"humanoid",
			"ai_none",
			{ "sword", "bow" },
			{ "body_leather" },
			0.1
			) },
		{ "villager_man", TemplateCreaturePreset(
			"villager_man",
			"Man",
			Glyph('h', TCODColor::lightAmber),
			0.8,
			0.6,
			"humanoid",
			"ai_villager",
			{ "dagger" } 
			) },
		{ "villager_woman", TemplateCreaturePreset(
			"villager_woman",
			"Woman",
			Glyph('h', TCODColor::lightAmber),
			0.7,
			0.6,
			"humanoid",
			"ai_villager",
			{ "dagger" }
			) },
		{ "villager_child", TemplateCreaturePreset(
			"villager_child",
			"Child",
			Glyph('c', TCODColor::lightAmber),
			0.2,
			0.2,
			"humanoid",
			"ai_villager"
			) },
		{ "villager_blacksmith", TemplateCreaturePreset(
			"villager_blacksmith",
			"Blacksmith",
			Glyph('b', TCODColor::lightGrey),
			0.8,
			0.8,
			"humanoid",
			"ai_blacksmith",
			{ "sword" },
			{ "body_leather" }) },
		{ "villager_alchemist", TemplateCreaturePreset(
			"villager_alchemist",
			"Alchemist",
			Glyph('a', TCODColor::lightBlue),
			0.6,
			0.3,
			"humanoid",
			"ai_alchemist",
			{ "staff" },
			{},
			0.3) },
		{ "goblin_melee", TemplateCreaturePreset(
			"goblin_melee",
			"Goblin",
			Glyph('g', TCODColor::chartreuse),
			0.2,
			0.3,
			"humanoid",
			"ai_monster",
			{ "dagger" },
			{ "body_leather", "head_leather" }) },
		{ "goblin_ranged", TemplateCreaturePreset(
			"goblin_ranged",
			"Goblin",
			Glyph('g', TCODColor::darkChartreuse),
			0.2,
			0.1,
			"humanoid",
			"ai_monster",
			{ "bow" },
			{ "body_leather", "head_leather" }) },
		{ "goblin_king", TemplateCreaturePreset(
			"goblin_king",
			"The Goblin King",
			Glyph('G', TCODColor::darkLime),
			0.6,
			0.2,
			"giant",
			"ai_monster",
			{ "mace" },
			{ "head_leather" },
			0.2
			) }
	};
	armorTemplates = std::unordered_map<std::string, TemplateArmor>{
		{ "head_leather", TemplateArmor(
			GameObject::ARMOR_HEAD,
			"Leather cap",
			Glyph('c', TCODColor::lighterSepia),
			0.5,
			0.3,
			0.3) },
		{ "body_leather", TemplateArmor(
			GameObject::ARMOR_BODY,
			"Leather body",
			Glyph('B', TCODColor::lighterSepia),
			5.0,
			0.4,
			0.6) },
		{ "hand_leather", TemplateArmor(
			GameObject::ARMOR_HAND,
			"Leather gloves",
			Glyph('g', TCODColor::lighterSepia),
			0.5,
			0.3,
			0.3,
			2) },
		{ "leg_leather", TemplateArmor(
			GameObject::ARMOR_LEG,
			"Leather boots",
			Glyph('b', TCODColor::lighterSepia),
			1.0,
			0.3,
			0.4,
			2) },
	};
	weaponTemplates = std::unordered_map<std::string, TemplateWeapon>{
		{ "sword", TemplateWeapon(
			GameObject::WEAPON_MELEE,
			"Sword",
			Glyph('s', TCODColor::lighterGrey),
			7.0,
			0.6,
			0.7,
			"skill_sword") },
		{ "dagger", TemplateWeapon(
			GameObject::WEAPON_MELEE,
			"Dagger",
			Glyph('d', TCODColor::lighterGrey),
			0.5,
			0.3,
			0.6,
			"skill_dagger") },
		{ "staff", TemplateWeapon(
			GameObject::WEAPON_MELEE,
			"Staff",
			Glyph('S', TCODColor::lighterSepia),
			4.0,
			0.5,
			0.5,
			"skill_staff",
			2) },
		{ "mace", TemplateWeapon(
			GameObject::WEAPON_MELEE,
			"Mace",
			Glyph('m', TCODColor::lighterGrey),
			9.0,
			0.6,
			0.8,
			"skill_mace") },
		{ "bow", TemplateWeapon(
			GameObject::WEAPON_RANGED,
			"Bow",
			Glyph('B', TCODColor::lighterSepia),
			4.0,
			0.4,
			0.4,
			"skill_bow",
			2) }
	};
	accessoryTemplates = std::unordered_map<std::string, TemplateAccessory>{
		{ "ring", TemplateAccessory(
			"Ring",
			Glyph('r', TCODColor::lighterOrange),
			0.300,
			0.10
			) },
		{ "amulet", TemplateAccessory(
			"Amulet",
			Glyph('a', TCODColor::lighterOrange),
			0.600,
			0.30
			) }
	};
	consumableTemplates = std::unordered_map<std::string, TemplateConsumable>{
		{ "potion", TemplateConsumable(
			"Potion",
			Glyph('p', TCODColor::lighterViolet),
			1.2,
			1.5,
			0.3
			) },
		{ "root", TemplateConsumable(
			"Root",
			Glyph('r', TCODColor::lighterSepia),
			0.8,
			0.7,
			0.8 
			) },
		{ "shroom", TemplateConsumable(
			"Shroom",
			Glyph('s', TCODColor::lighterAmber),
			0.6,
			0.2,
			1.8
			) }
	};
}
