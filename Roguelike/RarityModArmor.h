#pragma once
#include "ArmorEffect.h"
#include <vector>
#include <memory>

class Armor;
class RarityModArmor
{
public:
	std::string name;
	std::vector<std::shared_ptr<ArmorEffect>> effects;

	void apply(Armor &armor);

	RarityModArmor(std::string name, std::vector<std::shared_ptr<ArmorEffect>> effects) :
		name(name), effects(effects){};
};

