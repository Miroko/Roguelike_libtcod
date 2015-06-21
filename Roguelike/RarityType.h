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

const RarityType RARITY_COMMON = RarityType("Common", TCODColor::lightestCyan);
const RarityType RARITY_UNCOMMON = RarityType("Uncommon", TCODColor::lightestAzure);
const RarityType RARITY_RARE = RarityType("Rare", TCODColor::lightestPurple);
const RarityType RARITY_EPIC = RarityType("Epic", TCODColor::lightestGreen);
const RarityType RARITY_UNIQUE = RarityType("Unique", TCODColor::lightestAmber);

