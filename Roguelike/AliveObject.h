#pragma once
#include "DynamicObject.h"
#include "Weapon.h"
#include "Armor.h"
#include "AliveObjectEffect.h"
#include "AliveObjectAi.h"
#include "PointerContainer.h"
#include "Consumable.h"
#include <memory>

class AliveObject : public DynamicObject
{
	
public:
	AliveObjectAi ai;

	//Equipment
	std::shared_ptr<Weapon> weapon = nullptr;
	std::shared_ptr<Armor> armorHead = nullptr;
	std::shared_ptr<Armor> armorBody = nullptr;
	std::shared_ptr<Armor> armorHand = nullptr;
	std::shared_ptr<Armor> armorLeg = nullptr;
	void equip(std::shared_ptr<Item> equipment);

	//Effects
	PointerContainer<AliveObjectEffect> effects;
	void addEffect(std::shared_ptr<AliveObjectEffect> effect);
	void consume(std::shared_ptr<Item> consumable);

	void damage(DynamicObject &target);
	void attackMelee(DynamicObject &target);
	void attackRanged(DynamicObject &target);

	void onTakeDamage(DynamicObject &attacker, int amount);

	void update();

	AliveObject(Glyph glyph, std::string name, Size size, int health, const LootContainer &loot) :
		DynamicObject(glyph, name, size, true, health, loot){};
};