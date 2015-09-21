#pragma once
#include "DynamicObject.h"
#include "CreatureInventory.h"
#include "CreatureEffect.h"
#include "CreatureAi.h"
#include "CreatureLimb.h"
#include "RarityMod.h"
#include "WeaponAction.h"

class CreatureSkill;
class Creature : public DynamicObject, public RarityMod
{
private:
	bool waitedLastTurn = true;

	int staminaCurrent;
	int staminaMax;

	int magicCurrent;
	int magicMax;

public:
	std::string presetId;
	CreatureInventory inventory;
	std::shared_ptr<CreatureAi> ai;
	std::vector<CreatureLimb> limbs;
	std::vector<std::shared_ptr<CreatureEffect>> effects;

	int getHealthCurrent() override;
	int getHealthMax() override;

	int getStaminaCurrent();
	int getStaminaMax();
	void staminaHit(int amount);

	int getMagicCurrent();
	int getMagicMax();
	void magicHit(int amount);

	double getSpellPowerModifier();

	std::vector<std::pair<CreatureSkill*, double>> getCombatSkillsAndProficiencies();
	std::vector<std::pair<CreatureSkill*, double>> getWeaponSkillsAndProfiencies();
	std::vector<std::pair<CreatureSkill*, double>> getMagicSkillsAndProfiencies();
	bool executeSkillAction(CreatureSkill &skill, double skillProficiency, CreatureAction &action, double actionlProficiency, DynamicObject &target);

	void addEffect(std::shared_ptr<CreatureEffect> effect);
	void initAi(Area &area);

	void takeDamage(DynamicObject &attacker, double amount) override;
	void onDeath() override;
	bool move(Point2D &location) override;
	void onMove() override;
	void update() override;

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	Creature(std::string presetId, RarityMod rarityMod, DynamicObject dynamicObject, int stamina, int magic,
		std::shared_ptr<CreatureAi> ai, std::vector<CreatureLimb> limbs) :
		presetId(presetId),
		RarityMod(rarityMod),
		DynamicObject(dynamicObject),
		limbs(limbs),
		ai(ai),
		staminaCurrent(stamina),
		staminaMax(stamina),
		magicCurrent(magic),
		magicMax(magic){
		inventory.owner = this;
		ai->owner = this;
	};
};