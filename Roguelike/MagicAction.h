#pragma once
#include "CreatureAction.h"
#include <vector>
#include <memory>

class CreatureEffect;
class MagicAction : public CreatureAction
{
public:
	double staminaCostModifier;
	double magicCostModifier;

	std::vector<std::shared_ptr<CreatureEffect>> effects;

	bool CreatureAction::execute(Creature &executer, double skillModifier, GameObject &actionObject, DynamicObject &target) override;

	MagicAction(std::string name, std::string logDescription, double profiencyModifier, int range, double staminaCostModifier,
		double magicCostModifier, std::vector<std::shared_ptr<CreatureEffect>> effects) :
		CreatureAction(name, logDescription, profiencyModifier, range),
		staminaCostModifier(staminaCostModifier),
		magicCostModifier(magicCostModifier),
		effects(effects){}
};
