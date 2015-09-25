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
	enum StatType{
		HEALTH,
		STAMINA,
		MAGIC
	};
	StatType statType;
	std::string name;
	double modifier;
	int duration;

	virtual int getEffectAmountLeft() = 0;
	virtual std::string getDescription() = 0;
	virtual void apply(Creature &creature) = 0;
	virtual int getValue() = 0;
	virtual std::shared_ptr<CreatureEffect> clone() = 0;

	CreatureEffect(std::string name, double modifier, double durationFromMax,
		StatType statType, std::shared_ptr<VisualEffect> visualEffectOnApply = nullptr);
	//defined in cpp
};

