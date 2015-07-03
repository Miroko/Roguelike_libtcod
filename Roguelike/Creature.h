#pragma once
#include "DynamicObject.h"
#include "CreatureInventory.h"
#include "CreatureAi.h"
#include "CreatureLimb.h"
#include "RarityType.h"
#include <deque>

class Creature : public DynamicObject
{
private:
	void damageMelee(Weapon &weapon, DynamicObject &target);
	void damageRanged(Weapon &weapon, DynamicObject &target);

public:
	std::string presetId;
	CreatureInventory inventory;
	std::shared_ptr<CreatureAi> ai;
	std::vector<CreatureLimb> limbs;
	std::deque<std::shared_ptr<CreatureEffect>> effects;
	RarityType &rarity;
	std::vector<RarityModCreature*> rarityMods;

	void addEffect(std::shared_ptr<CreatureEffect> effect);
	void attack(DynamicObject &target);
	void onTakeDamage(DynamicObject &attacker, int amount);
	void onDeath();
	void changeAi(std::shared_ptr<CreatureAi> newAi);
	void initAi();
	void update();

	Creature(std::string name, std::string presetId, Glyph glyph, Type type, int health, RarityType &rarity, std::vector<RarityModCreature*> mods, std::shared_ptr<CreatureAi> ai, std::vector<CreatureLimb> limbs) :
		DynamicObject(
		name,
		type,
		glyph,
		health),
		presetId(presetId),
		limbs(limbs),
		ai(ai),
		rarity(rarity),
		rarityMods(mods){};
};