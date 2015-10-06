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
#include "Container.h"
#include "Wall.h"
#include "Floor.h"
#include "Water.h"
#include "Portal.h"
#include "CreatureEffectHealth.h"
#include "CreatureEffectMagic.h"
#include "CreatureEffectStamina.h"
#include "WeaponAction.h"
#include "MagicAction.h"
#include "ParticleSplash.h"
#include "ParticleSpiralUp.h"

void ObjectLibrary::init(){
	tiles = std::unordered_map<std::string, std::shared_ptr<Tile>>{
		{ "house_wall_wood", std::shared_ptr<Tile>(new Wall("Wooden house wall", Glyph(TCODColor::darkerSepia, 1.0))) },
		{ "house_wall_stone", std::shared_ptr<Tile>(new Wall("Stone house wall", Glyph(TCODColor(50, 50, 50), 1.0))) },
		{ "house_floor_wood", std::shared_ptr<Tile>(new Floor("Wooden house floor", Glyph(TCODColor::darkestSepia))) },
		{ "path_sand", std::shared_ptr<Tile>(new Floor("Sand path", Glyph(TCODColor(14, 11, 6)), 5.0f)) },
		{ "forest_wall_tree", std::shared_ptr<Tile>(new Wall("Tree", Glyph(TCODColor(5, 20, 5), TCODColor::darkerChartreuse, TCOD_CHAR_SPADE, 0.8))) },
		{ "forest_floor_grass", std::shared_ptr<Tile>(new Floor("Land", Glyph(TCODColor(5, 20, 5)))) },
		{ "forest_floor_stone", std::shared_ptr<Tile>(new Floor("Stone floor", Glyph(TCODColor(30, 30, 30)))) },
		{ "forest_wall_stone", std::shared_ptr<Tile>(new Wall("Stone", Glyph(TCODColor(45, 45, 45), 1.0))) },
		{ "forest_portal", std::shared_ptr<Tile>(new Portal("Exit", Glyph(TCODColor(0, 10, 0), TCODColor::darkerChartreuse, '>'))) },
		{ "cave_wall_wood", std::shared_ptr<Tile>(new Wall("Wooden column", Glyph(TCODColor::darkerSepia, 1.0))) },
		{ "cave_wall_stone1", std::shared_ptr<Tile>(new Wall("Cave wall", Glyph(TCODColor::grey, 1.0))) },
		{ "cave_wall_stone2", std::shared_ptr<Tile>(new Wall("Cave wall", Glyph(TCODColor::darkGrey, 1.0))) },
		{ "cave_floor_stone1", std::shared_ptr<Tile>(new Floor("Cave floor", Glyph(TCODColor(35, 35, 35)))) },
		{ "cave_floor_stone2", std::shared_ptr<Tile>(new Floor("Cave floor", Glyph(TCODColor(25, 25, 25)))) },
		{ "cave_portal", std::shared_ptr<Tile>(new Portal("Tunnel", Glyph(TCODColor(15, 15, 15), TCODColor(45, 45, 45), '>'))) },
		{ "cave_water", std::shared_ptr<Tile>(new Water("Water", Glyph(TCODColor::darkestBlue))) }
	};
	operatables = std::unordered_map<std::string, std::shared_ptr<OperatableObject>>{
		{ "door_wood", std::shared_ptr<OperatableObject>(new Door(
			"Wooden door",
			Glyph(TCODColor::darkestSepia, TCODColor::darkerSepia, 'D', 0.0),
			Glyph(TCODColor::darkerSepia, TCODColor::darkestSepia, 'D', 1.0),
			500)) },
		{ "bed_wood", std::shared_ptr<OperatableObject>(new Bed(
			"Wooden bed",
			Glyph(TCODColor::darkerSepia, TCODColor::darkSepia, 'B'),
			500)) },
		{ "forge", std::shared_ptr<OperatableObject>(new Forge()) },
		{ "anvil", std::shared_ptr<OperatableObject>(new Anvil()) },
		{ "alchemy_table1", std::shared_ptr<OperatableObject>(new AlchemyTable(
			"Alchemy table",
			Glyph(TCODColor::darkSepia, TCODColor::lightViolet, '%'))) },
		{ "alchemy_table2", std::shared_ptr<OperatableObject>(new AlchemyTable(
			"Alchemy table",
			Glyph(TCODColor::darkSepia, TCODColor::lightSea, '%'))) },
		{ "barrel_wood", std::shared_ptr<OperatableObject>(new Container(
			"Wooden barrel",
			Glyph('B', TCODColor::darkerSepia, 0.7),
			Glyph('B', TCODColor::darkSepia, 0.7),
			100, 0.10, true)) },
		{ "chest_wood_small", std::shared_ptr<OperatableObject>(new Container(
			"Small wooden chest",
			Glyph(TCODColor::darkestSepia, TCODColor::darkerSepia, 'c', 0.2),
			Glyph(TCODColor::darkerSepia, TCODColor::darkSepia, 'c', 0.2),
			300, 0.50)) },
		{ "chest_wood_large", std::shared_ptr<OperatableObject>(new Container(
			"Large wooden chest",
			Glyph(TCODColor::darkerSepia, TCODColor::darkSepia, 'C', 0.6),
			Glyph(TCODColor::darkSepia, TCODColor::sepia, 'C', 0.6),
			1200, 1.50, true)) },
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
		{ "strike", std::shared_ptr<CreatureAction>(new WeaponAction("Basic strike", "Strikes", 1.00, 1, 1.10, 1.00, 1.30, 1.00)) },
		{ "stab", std::shared_ptr<CreatureAction>(new WeaponAction("Basic stab", "Stabs", 1.00, 1, 1.50, 1.20, 1.20, 1.00)) },
		{ "slash", std::shared_ptr<CreatureAction>(new WeaponAction("Basic slash", "Slashes", 1.00, 1, 1.00, 1.20, 1.20, 1.00)) },
		{ "swing", std::shared_ptr<CreatureAction>(new WeaponAction("Basic swing", "Swings", 1.00, 1, 1.30, 0.90, 1.30, 1.20)) },
		{ "smash", std::shared_ptr<CreatureAction>(new WeaponAction("Basic smash", "Smashes", 1.00, 1, 1.70, 0.60, 1.70, 1.80)) },
		{ "shot", std::shared_ptr<CreatureAction>(new WeaponAction("Basic shot", "Shoots", 1.00, 8, 1.00, 1.20, 1.20, 1.10)) },
		//fire
		{ "fireball", std::shared_ptr<CreatureAction>(new MagicAction("Fireball", "Fireball", 0.70, 5, 0.60, 0.20,
			{ 
			std::shared_ptr<CreatureEffect>(new CreatureEffectHealth("Burning", -0.30, 0.30,
				std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::orange), 3, 21)),
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::grey), 3, 21)),
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkOrange), 3, 16))
			})))),
			std::shared_ptr<CreatureEffect>(new CreatureEffectStamina("Heat", -0.20, 0.40)) 
			},
			std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::orange), 4, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::orange), 4, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkOrange), 3, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkOrange), 3, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::yellow), 4, 12))
			})), CreatureAction::IN_RANGE))
		},
		//frost
		{ "frostball", std::shared_ptr<CreatureAction>(new MagicAction("Frostball", "Frostball", 0.70, 7, 0.40, 0.30,
			{ 
			std::shared_ptr<CreatureEffect>(new CreatureEffectHealth("Freezing", -0.20, 0.20,
				std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::lightestBlue), 3, 21)),
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::lightestBlue), 3, 21)),
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::lighterBlue), 3, 16))
			})))),
			std::shared_ptr<CreatureEffect>(new CreatureEffectStamina("Cold", -0.30, 0.60))
			},
			std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightestBlue), 2, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightestBlue), 2, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lighterBlue), 2, 12)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightBlue), 2, 10))
			})), CreatureAction::IN_RANGE))
		},
		//restoration
		{ "restoration", std::shared_ptr<CreatureAction>(new MagicAction("Restoration", "Restoration", 0.70, 1, 0.10, 0.20,
			{ 
			std::shared_ptr<CreatureEffect>(new CreatureEffectHealth("Restore", +0.01, 2.50,
				std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkestGreen), 3, 21)),
			})))),
			std::shared_ptr<CreatureEffect>(new CreatureEffectStamina("Restore", +0.02, 3.00,
				std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkestSky), 3, 21)),
			}))))
			},
			std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{	
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkestGreen), 2, 6)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkestSky), 2, 6))
			})), CreatureAction::SELF))
		}
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
		{ creatureAction["fireball"] })) },
		{ "skill_frost", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::MAGIC, "Frost Magic",
		{ creatureAction["frostball"] })) },
		{ "skill_restoration", std::shared_ptr<CreatureSkill>(new CreatureSkill(CreatureSkill::MAGIC, "Restoration Magic",
		{ creatureAction["restoration"] })) }
	};
	creatureBaseTemplates = std::unordered_map<std::string, TemplateCreatureBase>{
		{ "humanoid", TemplateCreatureBase({
			CreatureLimb("Head", 0.4f, GameObject::ARMOR_HEAD, false, GameObject::ACCESSORY_AMULET, 1),
			CreatureLimb("Body", 0.8f, GameObject::ARMOR_BODY, 0),
			CreatureLimb("Left arm", 0.7f, GameObject::ARMOR_HAND, true, GameObject::ACCESSORY_RING, 2),
			CreatureLimb("Right arm", 0.7f, GameObject::ARMOR_HAND, true, GameObject::ACCESSORY_RING, 2),
			CreatureLimb("Left leg", 0.6f, GameObject::ARMOR_LEG),
			CreatureLimb("Right leg", 0.6f, GameObject::ARMOR_LEG) },
			std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkerRed), 3, 9)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkRed), 2, 6)) })))
		},
		{ "giant", TemplateCreatureBase({
			CreatureLimb("Head", 0.9f, GameObject::ARMOR_HEAD, false, GameObject::ACCESSORY_AMULET, 1),
			CreatureLimb("Body", 1.0f, GameObject::ARMOR_BODY),
			CreatureLimb("Left arm", 0.9f, GameObject::ARMOR_HAND, true),
			CreatureLimb("Right arm", 0.9f, GameObject::ARMOR_HAND, true),
			CreatureLimb("Left leg", 1.0f, GameObject::ARMOR_LEG, 0),
			CreatureLimb("Right leg", 1.0f, GameObject::ARMOR_LEG, 0) },
			std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkerRed), 3, 9)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkerRed), 2, 7)),
				std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkRed), 2, 6)) })))
		}
	};
	creaturePresetTemplates = std::unordered_map<std::string, TemplateCreaturePreset>{
		{ "player", TemplateCreaturePreset(
			"player",
			"Player",
			Glyph('@', TCODColor::lightAmber, 0.3),
			0.80,
			0.60,
			"humanoid",
			"ai_none",
			{ "sword", "bow" },
			{ "body_leather" },
			{ "amulet", "ring", "ring", "ring", "ring" },
			0.30
			) },
		{ "villager_man", TemplateCreaturePreset(
			"villager_man",
			"Man",
			Glyph('h', TCODColor::lightAmber, 0.3),
			0.80,
			0.60,
			"humanoid",
			"ai_villager",
			{ "dagger" } 
			) },
		{ "villager_woman", TemplateCreaturePreset(
			"villager_woman",
			"Woman",
			Glyph('h', TCODColor::lightAmber, 0.3),
			0.70,
			0.60,
			"humanoid",
			"ai_villager",
			{ "dagger" }
			) },
		{ "villager_child", TemplateCreaturePreset(
			"villager_child",
			"Child",
			Glyph('c', TCODColor::lightAmber, 0.1),
			0.20,
			0.20,
			"humanoid",
			"ai_villager"
			) },
		{ "villager_blacksmith", TemplateCreaturePreset(
			"villager_blacksmith",
			"Blacksmith",
			Glyph('b', TCODColor::lightGrey, 0.3),
			0.80,
			0.80,
			"humanoid",
			"ai_blacksmith",
			{ "sword" },
			{ "body_leather" }
			) },
		{ "villager_alchemist", TemplateCreaturePreset(
			"villager_alchemist",
			"Alchemist",
			Glyph('a', TCODColor::lightBlue, 0.3),
			0.60,
			0.30,
			"humanoid",
			"ai_alchemist",
			{ "staff" },
			{},
			{ "amulet", "ring", "ring" },
			0.50
			) },
		{ "goblin_melee", TemplateCreaturePreset(
			"goblin_melee",
			"Goblin",
			Glyph('g', TCODColor::chartreuse, 0.2),
			0.25,
			0.30,
			"humanoid",
			"ai_monster",
			{ "dagger" },
			{ "body_leather" }
			) },
		{ "goblin_ranged", TemplateCreaturePreset(
			"goblin_ranged",
			"Goblin Hunter",
			Glyph('g', TCODColor::darkerChartreuse, 0.2),
			0.20,
			0.30,
			"humanoid",
			"ai_monster",
			{ "bow" },
			{ "head_leather" }
			) },
		{ "goblin_magic", TemplateCreaturePreset(
			"goblin_magic",
			"Goblin Shaman",
			Glyph('g', TCODColor(64, 96, 64), 0.2),
			0.15,
			0.20,
			"humanoid",
			"ai_monster",
			{ "dagger" },
			{ },
			{ "amulet", "ring", "ring" },
			0.15 
			) },
		{ "goblin_king", TemplateCreaturePreset(
			"goblin_king",
			"The Goblin King",
			Glyph('G', TCODColor::darkLime, 0.6),
			0.6,
			0.2,
			"giant",
			"ai_monster",
			{ "mace" },
			{ "head_leather" },
			{ "amulet" },
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
			GameObject::ACCESSORY_RING,
			"Ring",
			Glyph('r', TCODColor::lighterOrange),
			0.300,
			0.40
			) },
		{ "amulet", TemplateAccessory(
			GameObject::ACCESSORY_AMULET,
			"Amulet",
			Glyph('a', TCODColor::lighterOrange),
			0.800,
			0.90
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
