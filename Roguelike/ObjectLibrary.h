#pragma once
#include "StaticObject.h"
#include "Portal.h"
#include "LootContainer.h"
#include "EquipmentContainer.h"
#include "Heal.h"
#include "Area.h"
#include "RarityType.h"
#include <map>
#include <memory>

class ObjectLibrary
{
public:
	template <typename T> static std::shared_ptr<T> createNew(T &templateObject){
		return std::shared_ptr<T>(new T(templateObject));
	}

	static StaticObject FOREST_LAND;
	static StaticObject FOREST_TREE;

	static StaticObject STONE_WALL;
	static StaticObject STONE_FLOOR;

	static StaticObject WOOD_WALL;
	static StaticObject WOOD_FLOOR; 

	static Portal FOREST_PORTAL;
	static Portal CAVE_PORTAL;

	static Weapon DAGGER;
	static Weapon SWORD;
	static Weapon BOW;

	static Armor LEATHER_HEAD;
	static Armor LEATHER_BODY;
	static Armor LEATHER_HAND;
	static Armor LEATHER_LEG;

	static Heal HEAL;
	static Consumable HEALTH_POTION;

	static LootContainer MAN_LOOT;
	static EquipmentContainer MAN_EQUIPMENT;
	static Creature MAN;

	static LootContainer GOBLIN_LOOT;
	static EquipmentContainer GOBLIN_EQUIPMENT;
	static Creature GOBLIN;

	static LootContainer DOOR_LOOT;
	static Door WOOD_DOOR;

	static std::shared_ptr<Creature> generateCreature(Creature &templateCreature, RarityType &rarity, EquipmentContainer &equipment, LootContainer &loot);
	static std::shared_ptr<Weapon> generateWeapon(Weapon &templateWeapon, RarityType &rarity);
	static std::shared_ptr<Armor> generateArmor(Armor &templateArmor, RarityType &rarity);
	static std::shared_ptr<Consumable> generateConsumable(Consumable &templateConsumable);
	static std::shared_ptr<Door> generateDoor(Door &templateDoor, LootContainer &loot);

	static void generateLootDrop(Area &toArea, DynamicObject &dynamicObject);

	ObjectLibrary(){};
};

