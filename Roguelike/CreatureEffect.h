#pragma once
#include <string>

class Creature;
class CreatureEffect
{
public:
	virtual std::string getDescription() = 0;
	virtual void apply(Creature &creature) = 0;

	CreatureEffect(){};
};

