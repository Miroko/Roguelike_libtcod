#pragma once
#include "CreatureAction.h"

class Weapon;
class DynamicObject;
class Creature;
class WeaponAction : public CreatureAction
{
public:
	double staminaCostModifier;
	double damageModifier;
	double durabilityModifier;
	double accuracyModifier;

	void execute(Creature &executer, Weapon &actionObject, DynamicObject &target);

	WeaponAction(std::string name, std::string logDescription, double damageModifier, double accuracyModifier, double staminaCostModifier, double durabilityModifier) :
		CreatureAction(name, logDescription),
		staminaCostModifier(staminaCostModifier),
		damageModifier(damageModifier),
		accuracyModifier(accuracyModifier),
		durabilityModifier(durabilityModifier){};
	WeaponAction(){}
};

