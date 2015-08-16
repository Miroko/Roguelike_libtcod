#pragma once
#include <memory>
#include <string>

class Creature;
class CreatureEffect
{
public:
	int duration;
	virtual std::string getDescription() = 0;
	virtual void apply(Creature &creature) = 0;
	virtual int getValue() = 0;
	virtual std::shared_ptr<CreatureEffect> clone() = 0;

	CreatureEffect(int duration):
		duration(duration){};
};

