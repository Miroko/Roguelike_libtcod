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

	int getMagicCost(Creature &user);
	int getStaminaCost(Creature &user);

	bool CreatureAction::execute(Creature &executer, double skillModifier, GameObject &actionObject, DynamicObject &target) override;

	void GuiObject::renderToFrame(GuiFrame &frame, Rectangle &renderBounds) override;

	MagicAction(std::string name, std::string logDescription, double actionProficiency, int range, double staminaCostModifier,
		double magicCostModifier, std::vector<std::shared_ptr<CreatureEffect>> effects,
		std::shared_ptr<VisualEffect> visualEffectOnExecution = nullptr,
		TargetType targetType = TargetType::IN_RANGE)
		:
		CreatureAction(name, logDescription, actionProficiency, range, visualEffectOnExecution, targetType),
		staminaCostModifier(staminaCostModifier),
		magicCostModifier(magicCostModifier),
		effects(effects){}
};
