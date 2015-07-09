#pragma once
#include "Tile.h"
#include "TemplateCreature.h"
#include "TemplateCreaturePreset.h"
#include "CreatureAi.h"
#include "TemplateWeapon.h"
#include "TemplateArmor.h"
#include "Door.h"
#include "Item.h"
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
	float headDefence;
	float bodyDefence;
	float handDefence;
	float legDefence;
	float rangedMultiplier;

	std::list<RarityType> rarityTypes;
	std::unordered_map<std::string, std::unique_ptr<Tile>> tiles;
	std::unordered_map<std::string, std::unique_ptr<OperatableObject>> operatableObjects;
	std::unordered_map<std::string, TemplateWeapon> weaponTemplates;
	std::unordered_map<std::string, TemplateArmor> armorTemplates;
	std::unordered_map<std::string, std::unique_ptr<CreatureAi>> creatureAis;
	std::unordered_map<std::string, TemplateCreature> creatureTemplates;
	std::unordered_map<std::string, TemplateCreaturePreset> creaturePresetTemplates;

	bool addTile(std::string id, std::unique_ptr<Tile> tile);
	bool addOperatable(std::string id, std::unique_ptr<OperatableObject> operatable);
	bool addWeaponTemplate(TemplateWeapon weaponTemplate);
	bool addArmorTemplate(TemplateArmor armorTemplate);
	void addRarity(RarityType rarity);
	bool addCreatureAi(std::string id, std::unique_ptr<CreatureAi> ai);
	bool addCreatureTemplate(TemplateCreature creatureTemplate);
	bool addCreaturePresetTemplate(TemplateCreaturePreset creaturePresetTemplate);
	Tile *getTile(std::string id);
	OperatableObject *getOperatable(std::string id);
	RarityType *getRarity(std::string id);
	RarityType *getRarity(float roll);
	TemplateWeapon *getTemplateWeapon(std::string id);
	TemplateArmor *getTemplateArmor(std::string id);
	CreatureAi *getAi(std::string id);
	TemplateCreature *getTemplateCreature(std::string id);
	TemplateCreaturePreset *getTemplateCreaturePreset(std::string id);

	void sortRarityTypes();

	void init();

	ObjectLibrary(){};
};
