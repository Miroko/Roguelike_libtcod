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
		double magicCostModifier, std::vector<std::shared_ptr<CreatureEffect>> effects, std::shared_ptr<VisualEffect> visualEffectOnExecution = nullptr) :
		CreatureAction(name, logDescription, profiencyModifier, range, visualEffectOnExecution),
		staminaCostModifier(staminaCostModifier),
		magicCostModifier(magicCostModifier),
		effects(effects){}
};
