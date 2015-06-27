#include "ObjectLibrary.h"
#include "HeavyRarityEffect.h"

RarityType RarityType::COMMON = [] {
	std::vector<std::shared_ptr<RarityEffect>> effects = std::vector<std::shared_ptr<RarityEffect>>({
		std::shared_ptr<RarityEffect>(new HeavyRarityEffect())
	});
	RarityType common = RarityType("Common", TCODColor::lightestCyan, 1.0, effects);
	return common;
}();

RarityType RarityType::UNCOMMON = [] {
	std::vector<std::shared_ptr<RarityEffect>> effects = std::vector<std::shared_ptr<RarityEffect>>({
		std::shared_ptr<RarityEffect>(new HeavyRarityEffect())
	});
	RarityType uncommon = RarityType("Uncommon", TCODColor::lighterSky, 1.3, effects);
	return uncommon;
}();

RarityType RarityType::RARE = [] {
	std::vector<std::shared_ptr<RarityEffect>> effects = std::vector<std::shared_ptr<RarityEffect>>({
		std::shared_ptr<RarityEffect>(new HeavyRarityEffect())
	});
	RarityType rare = RarityType("Rare", TCODColor::lighterBlue, 1.8, effects);
	return rare;
}();

RarityType RarityType::EPIC = [] {
	std::vector<std::shared_ptr<RarityEffect>> effects = std::vector<std::shared_ptr<RarityEffect>>({
		std::shared_ptr<RarityEffect>(new HeavyRarityEffect())
	});
	RarityType epic = RarityType("Epic", TCODColor::lightGreen, 2.6, effects);
	return epic;
}();

RarityType RarityType::UNIQUE = [] {
	std::vector<std::shared_ptr<RarityEffect>> effects = std::vector<std::shared_ptr<RarityEffect>>({
		std::shared_ptr<RarityEffect>(new HeavyRarityEffect())
	});
	RarityType unique = RarityType("Unique", TCODColor::lightOrange, 4.0, effects);
	return unique;
}();

StaticObject ObjectLibrary::FOREST_LAND = StaticObject("Land", Glyph(TCODColor::darkestGreen, TCODColor(5, 20, 5)));
StaticObject ObjectLibrary::FOREST_TREE = StaticObject("Tree", Glyph(TCODColor::darkerChartreuse, TCODColor(5, 20, 5), TCOD_CHAR_SPADE), true, false);
StaticObject ObjectLibrary::STONE_WALL = StaticObject("Stone", Glyph(TCODColor::darkerGrey, TCODColor::darkerGrey), true, false);
StaticObject ObjectLibrary::STONE_FLOOR = StaticObject("Stone floor", Glyph(TCODColor::darkestGrey, TCODColor::darkestGrey));
StaticObject ObjectLibrary::WOOD_WALL = StaticObject("Wooden wall", Glyph(TCODColor::darkerSepia, TCODColor::darkerSepia), true, false);
StaticObject ObjectLibrary::WOOD_FLOOR = StaticObject("Wooden floor", Glyph(TCODColor::darkestSepia, TCODColor::darkestSepia));

Portal ObjectLibrary::FOREST_PORTAL = Portal("Forest entrance", Glyph(TCODColor::lightGreen, FOREST_LAND.glyph.bgColor, '>'));
Portal ObjectLibrary::CAVE_PORTAL = Portal("Cave entrance", Glyph(TCODColor::lightGrey, STONE_FLOOR.glyph.bgColor, '>'));

Weapon ObjectLibrary::DAGGER = Weapon("Dagger", Glyph(TCODColor::lightGrey, 'd'), 0.5, 2, Item::WEAPON_MELEE);
Weapon ObjectLibrary::SWORD = Weapon("Sword", Glyph(TCODColor::lightGrey, 's'), 4.0, 8, Item::WEAPON_MELEE);
Weapon ObjectLibrary::BOW = Weapon("Bow", Glyph(TCODColor::lightGrey, 'B'), 3.0, 5, Item::WEAPON_RANGED);

Armor ObjectLibrary::LEATHER_HEAD = Armor("Leather cap", Glyph(TCODColor::lightGrey, 'c'), 0.5, 1, Item::ARMOR_HEAD);
Armor ObjectLibrary::LEATHER_BODY = Armor("Leather body", Glyph(TCODColor::lightGrey, 'B'), 5.0, 3, Item::ARMOR_BODY);
Armor ObjectLibrary::LEATHER_HAND = Armor("Leather gloves", Glyph(TCODColor::lightGrey, 'g'), 0.5, 1, Item::ARMOR_HAND);
Armor ObjectLibrary::LEATHER_LEG = Armor("Leather boots", Glyph(TCODColor::lightGrey, 'b'), 2.0, 2, Item::ARMOR_LEG);

Heal ObjectLibrary::HEAL = Heal(1, 5);
Consumable ObjectLibrary::HEALTH_POTION = Consumable("Health potion", std::vector<AliveObjectEffect*>({&HEAL}), Glyph(TCODColor::lightRed, 'p'), 0.2);

LootContainer ObjectLibrary::MAN_LOOT = LootContainer(std::vector<Loot>({
	Loot(SWORD, 0.6)
}));
EquipmentContainer ObjectLibrary::MAN_EQUIPMENT = EquipmentContainer(std::vector<Equipment*>({
	&SWORD,
	&LEATHER_BODY
}));
Creature ObjectLibrary::MAN = Creature("Man", 'h', TCODColor::lighterAmber, 30);

LootContainer ObjectLibrary::GOBLIN_LOOT = LootContainer(std::vector<Loot>({
	Loot(DAGGER, 0.2),
	Loot(HEALTH_POTION, 0.2)
}));
EquipmentContainer ObjectLibrary::GOBLIN_EQUIPMENT = EquipmentContainer(std::vector<Equipment*>({
	&DAGGER,
	&LEATHER_BODY
}));
Creature ObjectLibrary::GOBLIN = Creature("Goblin", 'g', TCODColor::lighterChartreuse, 10);

LootContainer ObjectLibrary::DOOR_LOOT = LootContainer(std::vector<Loot>({}));
Door ObjectLibrary::WOOD_DOOR = Door("Wooden door", Glyph(TCODColor::darkSepia, TCODColor::darkestSepia, 'D'),	Glyph(TCODColor::sepia, TCODColor::darkerSepia, 'D'));


std::shared_ptr<Creature> ObjectLibrary::generateCreature(Creature &templateCreature, RarityType &rarity, EquipmentContainer &equipment, LootContainer &loot){
	std::shared_ptr<Creature> creature = std::shared_ptr<Creature>(new Creature(templateCreature));
	rarity.apply(*creature);
	equipment.equipOn(*creature);
	creature->loot = &loot;
	return creature;
}

std::shared_ptr<Weapon> ObjectLibrary::generateWeapon(Weapon &templateWeapon, RarityType &rarity){
	std::shared_ptr<Weapon> weapon = std::shared_ptr<Weapon>(new Weapon(templateWeapon));
	rarity.apply(*weapon);
	return weapon;
}

std::shared_ptr<Armor> ObjectLibrary::generateArmor(Armor &templateArmor, RarityType &rarity){
	std::shared_ptr<Armor> armor = std::shared_ptr<Armor>(new Armor(templateArmor));
	rarity.apply(*armor);
	return armor;
}

std::shared_ptr<Consumable> ObjectLibrary::generateConsumable(Consumable &templateConsumable){
	std::shared_ptr<Consumable> consumable = std::shared_ptr<Consumable>(new Consumable(templateConsumable));
	RarityType::COMMON.apply(*consumable);
	return consumable;
}

std::shared_ptr<Door> ObjectLibrary::generateDoor(Door &templateDoor, LootContainer &loot){
	std::shared_ptr<Door> door = std::shared_ptr<Door>(new Door(templateDoor));
	door->loot = &loot;
	return door;
}

void ObjectLibrary::generateLootDrop(Area &toArea, DynamicObject &dynamicObject){
	for (auto &item : dynamicObject.loot->generateLoot()){
		toArea.placeItem(item, dynamicObject.location);
	}
}