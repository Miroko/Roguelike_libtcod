
/*
#pragma once
#include "DynamicObject.h"
#include "Weapon.h"
#include "Armor.h"
#include "CreatureEffect.h"
#include "CreatureAi.h"
#include "CreatureLimb.h"
#include "Consumable.h"
#include <deque>
#include <memory>

class AliveObject : public DynamicObject
{
public:
	
	std::shared_ptr<CreatureAi> ai;
	std::vector<CreatureLimb> limbs;
	std::deque<std::shared_ptr<CreatureEffect>> effects;
	void addEffect(std::shared_ptr<CreatureEffect> effect);
	void damageMelee(std::shared_ptr<Weapon> weapon, std::shared_ptr<DynamicObject> target);
	void damageRanged(std::shared_ptr<Weapon> weapon, std::shared_ptr<DynamicObject> target);
	void onTakeDamage(DynamicObject &attacker, int amount);
	void initAi();
	void update();
	
	AliveObject(std::string name, Type type, Glyph glyph, int health, std::vector<CreatureLimb> limbs, std::shared_ptr<CreatureAi> ai) :
		DynamicObject(name, type, glyph, health), limbs(limbs), ai(ai){
	};
	
};
*/