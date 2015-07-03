#pragma once
#include <string>
#include <memory>

class Creature;
class Weapon;
class Armor;
class RarityType;
class ObjectFactory
{
public:
	float valueVariation = 0.20f;
	float lootPrevalenceFromRarityRatio = 0.20f;
	float lootRollMiss = 0.80f;
	int lootDropRolls = 6;

	std::shared_ptr<Creature> createCreaturePreset(std::string creaturePresetTemplateId, RarityType &rarity);
	std::shared_ptr<Weapon> createWeapon(std::string weaponTemplateId, RarityType &rarity);
	std::shared_ptr<Armor> createArmor(std::string weaponTemplateId, RarityType &rarity);

	std::shared_ptr<Creature> createCreaturePreset(std::string creaturePresetTemplateId, float rarityRoll);
	std::shared_ptr<Weapon> createWeapon(std::string weaponTemplateId, float rarityRoll);
	std::shared_ptr<Armor> createArmor(std::string weaponTemplateId, float rarityRoll);

	void generateLootDrop(Creature &creature);

	ObjectFactory(){};
};

