#pragma once
#include "CreatureEffect.h"
#include "Gui.h"

class CreatureEffectStamina : public CreatureEffect
{
public:
	int CreatureEffect::getEffectAmountLeft() override;
	std::string CreatureEffect::getDescription() override;
	void CreatureEffect::apply(Creature &creature) override;
	int CreatureEffect::getValue() override;
	std::shared_ptr<CreatureEffect> CreatureEffect::clone() override;

	CreatureEffectStamina(std::string name, double modifier, double durationFromMax, 
		std::shared_ptr<VisualEffect> visualEffectOnApply = nullptr) :
		CreatureEffect(name, modifier, durationFromMax, CreatureEffect::STAMINA, visualEffectOnApply){}
};

