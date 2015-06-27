#pragma once
#include "DynamicObject.h"
#include "Weapon.h"
#include "Armor.h"
#include "AliveObjectEffect.h"
#include "AliveObjectAi.h"
#include "Consumable.h"
#include <deque>
#include <memory>

class AliveObject : public DynamicObject
{	
public:
	AliveObjectAi ai;

	//Equipment
	Weapon *weapon = nullptr;
	Armor *armorHead = nullptr;
	Armor *armorBody = nullptr;
	Armor *armorHand = nullptr;
	Armor *armorLeg = nullptr;

	void equipItem(Equipment &equipment);

	//Effects
	std::deque<AliveObjectEffect*> effects;
	void addEffect(AliveObjectEffect &effect);
	void consume(Consumable &consumable);

	void damage(DynamicObject &target);
	void attackMelee(DynamicObject &target);
	void attackRanged(DynamicObject &target);

	void onTakeDamage(DynamicObject &attacker, int amount);

	virtual void update();

	AliveObject(std::string name, Glyph glyph, int health) :
		DynamicObject(name, glyph, health){};
};