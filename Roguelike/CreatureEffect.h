#pragma once
#include <memory>
#include <string>

class Creature;
class VisualEffect;
class CreatureEffect
{
private:
	std::shared_ptr<VisualEffect> visualEffectOnApply;

public:
	std::string name;
	double modifier;
	int duration;
	virtual std::string getDescription() = 0;
	virtual void apply(Creature &creature) = 0;
	virtual int getValue() = 0;

	virtual std::shared_ptr<CreatureEffect> clone() = 0;

	CreatureEffect(std::string name, double modifier, double durationFromMax, std::shared_ptr<VisualEffect> visualEffectOnApply = nullptr);
};

