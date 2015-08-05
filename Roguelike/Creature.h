#pragma once
#include "DynamicObject.h"
#include "CreatureInventory.h"
#include "CreatureAi.h"
#include "CreatureLimb.h"
#include "RarityType.h"

class Creature : public DynamicObject
{
private:
	bool waitedLastTurn = true;
	void damageMelee(Weapon &weapon, DynamicObject &target);
	void damageRanged(Weapon &weapon, DynamicObject &target);

public:
	std::string presetId;
	int staminaCurrent;
	int staminaMax;
	CreatureInventory inventory;
	std::shared_ptr<CreatureAi> ai;
	std::vector<CreatureLimb> limbs;
	std::vector<std::shared_ptr<CreatureEffect>> effects;
	RarityType &rarity;
	std::vector<RarityModCreature*> rarityMods;

	void addEffect(std::shared_ptr<CreatureEffect> effect);
	void attack(DynamicObject &target);
	void onTakeDamage(DynamicObject &attacker, int amount);
	void onDeath();
	bool move(Point2D &location);
	void onMove();
	void initAi(Area &area);
	void update();

	Creature(std::string name, std::string presetId, Glyph glyph, Type type, int health, int stamina, RarityType &rarity, std::vector<RarityModCreature*> mods, std::shared_ptr<CreatureAi> ai, std::vector<CreatureLimb> limbs) :
		DynamicObject(
		name,
		type,
		glyph,
		health),
		presetId(presetId),
		limbs(limbs),
		ai(ai),
		rarity(rarity),
		rarityMods(mods), 
		staminaCurrent(stamina),
		staminaMax(stamina){};
};