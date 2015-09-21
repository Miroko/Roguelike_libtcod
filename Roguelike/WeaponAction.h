#pragma once
#include "CreatureAction.h"

class WeaponAction : public CreatureAction
{
public:
	double staminaCostModifier;
	double damageModifier;
	double durabilityModifier;
	double accuracyModifier;

	bool CreatureAction::execute(Creature &executer, double skillModifier, GameObject &actionObject, DynamicObject &target) override;

	WeaponAction(std::string name, std::string logDescription, double profiencyModifier, int range, double damageModifier,
		double accuracyModifier, double staminaCostModifier, double durabilityModifier, std::shared_ptr<VisualEffect> visualEffectOnExecution = nullptr) :
		CreatureAction(name, logDescription, profiencyModifier, range, visualEffectOnExecution),
		staminaCostModifier(staminaCostModifier),
		damageModifier(damageModifier),
		accuracyModifier(accuracyModifier),
		durabilityModifier(durabilityModifier){};
	WeaponAction(){}
};

