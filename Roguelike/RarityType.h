#pragma once
#include "libtcod.hpp"
#include <string>

class RarityType
{
public:
	const TCODColor &color;
	std::string name;

	RarityType(std::string name, const TCODColor &color) : name(name), color(color){};
};
const RarityType COMMON = RarityType("Common", TCODColor::lightestCyan);
const RarityType UNCOMMON = RarityType("Uncommon", TCODColor::lightestAzure);
const RarityType RARE = RarityType("Rare", TCODColor::lightestPurple);
const RarityType EPIC = RarityType("Epic", TCODColor::lightestGreen);
const RarityType UNIQUE = RarityType("Unique", TCODColor::lightestAmber);

