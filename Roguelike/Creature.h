#pragma once
#include "DynamicObject.h"
#include "CreatureInventory.h"
#include "CreatureEffect.h"
#include "CreatureAi.h"
#include "CreatureLimb.h"
#include "RarityMod.h"
#include "WeaponAction.h"

class Creature : public DynamicObject, public RarityMod
{
private:
	bool waitedLastTurn = true;

public:
	std::string presetId;
	int staminaCurrent;
	int staminaMax;
	CreatureInventory inventory;
	std::shared_ptr<CreatureAi> ai;
	std::vector<CreatureLimb> limbs;
	std::vector<std::shared_ptr<CreatureEffect>> effects;

	void attack(std::vector<std::pair<Weapon*, WeaponAction*>> &weaponActions, DynamicObject &target);
	void onTakeDamage(DynamicObject &attacker, double amount);
	void onDeath();
	void addEffect(std::shared_ptr<CreatureEffect> effect);
	bool move(Point2D &location);
	void onMove();
	void initAi(Area &area);
	void update();

	Creature(std::string presetId, RarityMod rarityMod, DynamicObject dynamicObject, int stamina, std::shared_ptr<CreatureAi> ai, std::vector<CreatureLimb> limbs) :
		presetId(presetId),
		RarityMod(rarityMod),
		DynamicObject(dynamicObject),
		limbs(limbs),
		ai(ai),
		staminaCurrent(stamina),
		staminaMax(stamina){
		inventory.owner = this;
		ai->owner = this;
	};
};