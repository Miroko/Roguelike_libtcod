#pragma once
#include "CreatureAction.h"

class Weapon;
class WeaponAction : public CreatureAction
{
public:
	double staminaCostModifier;
	double damageModifier;
	double durabilityModifier;
	double accuracyModifier;

	int getStaminaCost(Creature &user, Weapon &actionWeapon);
	double getAccuracy(Creature &user, Weapon &actionWeapon);
	int getDamage(Creature &user, Weapon &actionWeapon);
	double getDurabilityCost(Creature &user, Weapon &actionWeapon);

	bool CreatureAction::execute(Creature &executer, double actionProficiency, GameObject &actionObject, DynamicObject &target) override;

	WeaponAction(std::string name, std::string logDescription, double actionProficiency, int range, double damageModifier,
		double accuracyModifier, double staminaCostModifier, double durabilityModifier,
		std::shared_ptr<VisualEffect> visualEffectOnExecution = nullptr, TargetType targetType = TargetType::IN_RANGE)
		:
		CreatureAction(name, logDescription, actionProficiency, range, visualEffectOnExecution, targetType),
		staminaCostModifier(staminaCostModifier),
		damageModifier(damageModifier),
		accuracyModifier(accuracyModifier),
		durabilityModifier(durabilityModifier){};
	WeaponAction(){}
};

