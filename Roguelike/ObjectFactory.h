#pragma once
#include "TemplateArmor.h"
#include "TemplateWeapon.h"
#include "TemplateConsumable.h"
#include "TemplateCreaturePreset.h"
#include "RarityType.h"
#include <string>
#include <memory>

class Creature;
class Weapon;
class Armor;
class Consumable;
class OperatableObject;
class ObjectFactory
{
public:
	std::shared_ptr<Creature> createCreature(std::string id, std::string rarity);
	std::shared_ptr<Weapon> createWeapon(std::string id, std::string rarity);
	std::shared_ptr<Armor> createArmor(std::string id, std::string rarity);
	std::shared_ptr<Consumable> createConsumable(std::string id, std::string rarity);
	std::shared_ptr<OperatableObject> createOperatable(std::string id);

	std::shared_ptr<Creature> createCreature(TemplateCreaturePreset &presetTemplate, RarityType &rarityType);
	std::shared_ptr<Weapon> createWeapon(TemplateWeapon &weaponTemplate, RarityType &rarityType);
	std::shared_ptr<Armor> createArmor(TemplateArmor &armorTemplate, RarityType &rarityType);
	std::shared_ptr<Consumable> createConsumable(TemplateConsumable &consumableTemplate, RarityType &rarityType);

	void generateLootDrop(Creature &creature);

	ObjectFactory(){};
};

