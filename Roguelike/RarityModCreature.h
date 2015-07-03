#pragma once
#include "CreatureEffect.h"
#include <vector>
#include <memory>

class Creature;
class RarityModCreature
{
public:
	std::string name;
	std::vector<std::shared_ptr<CreatureEffect>> effects;

	void apply(Creature &creature);

	RarityModCreature(std::string name, std::vector<std::shared_ptr<CreatureEffect>> effects) :
		name(name), effects(effects){};
};

