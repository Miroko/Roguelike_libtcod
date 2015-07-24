#pragma once
#include "Tile.h"
#include "TemplateCreature.h"
#include "TemplateCreaturePreset.h"
#include "CreatureAi.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "TemplatePotion.h"
#include "Door.h"
#include "Item.h"
#include "Potion.h"
#include "RarityType.h"
#include <unordered_map>
#include <memory>
#include <list>

class ObjectLibrary
{
public:
	float maxHealth;
	float maxDamage;
	float maxDefence;
	float maxWeight;

	std::list<RarityType> rarityTypes;
	std::unordered_map<std::string, RarityModCreature> creatureRarityMods;
	std::unordered_map<std::string, RarityModArmor> armorRarityMods;
	std::unordered_map<std::string, RarityModWeapon> weaponRarityMods;
	std::unordered_map<std::string, std::unique_ptr<Tile>> tiles;
	std::unordered_map<std::string, std::unique_ptr<OperatableObject>> operatableObjects;
	std::unordered_map<std::string, std::unique_ptr<CreatureAi>> creatureAis;
	std::unordered_map<std::string, TemplatePotion> potionTemplates;
	std::unordered_map<std::string, TemplateWeapon> weaponTemplates;
	std::unordered_map<std::string, TemplateArmor> armorTemplates;
	std::unordered_map<std::string, TemplateCreature> creatureTemplates;
	std::unordered_map<std::string, TemplateCreaturePreset> creaturePresetTemplates;

	void addRarity(RarityType rarity);
	bool addRarityModCreature(std::string id, RarityModCreature mod);
	bool addRarityModArmor(std::string id, RarityModArmor mod);
	bool addRarityModWeapon(std::string id, RarityModWeapon mod);
	bool addTile(std::string id, std::unique_ptr<Tile> tile);
	bool addOperatable(std::string id, std::unique_ptr<OperatableObject> operatable);
	bool addPotionTemplate(TemplatePotion potionTemplate);
	bool addWeaponTemplate(TemplateWeapon weaponTemplate);
	bool addArmorTemplate(TemplateArmor armorTemplate);
	bool addCreatureAi(std::string id, std::unique_ptr<CreatureAi> ai);
	bool addCreatureTemplate(TemplateCreature creatureTemplate);
	bool addCreaturePresetTemplate(TemplateCreaturePreset creaturePresetTemplate);
	Tile *getTile(std::string id);
	OperatableObject *getOperatable(std::string id);
	CreatureAi *getAi(std::string id);
	TemplatePotion *getTemplatePotion(std::string id);
	TemplateWeapon *getTemplateWeapon(std::string id);
	TemplateArmor *getTemplateArmor(std::string id);
	TemplateCreature *getTemplateCreature(std::string id);
	TemplateCreaturePreset *getTemplateCreaturePreset(std::string id);
	RarityType *getRarity(std::string id);
	RarityType *getRarity(float roll);
	RarityModCreature *getRarityModCreature(std::string id);
	RarityModArmor *getRarityModArmor(std::string id);
	RarityModWeapon *getRarityModWeapon(std::string id);

	void sortRarityTypes();
	void init();

	ObjectLibrary(){};
};
