#pragma once
#include "libtcod.hpp"
#include "RarityEffect.h"
#include <string>
#include <vector>

class RarityType
{
public:
	static RarityType COMMON;
	static RarityType UNCOMMON;
	static RarityType RARE;
	static RarityType EPIC;
	static RarityType UNIQUE;

	std::string name;
	const TCODColor &color;
	float effectMultiplier;

	std::vector<std::shared_ptr<RarityEffect>> effects;
	RarityEffect* getRandomEffect();

	void apply(Creature &creature);
	void apply(Weapon &weapon);
	void apply(Armor &armor);
	void apply(Consumable &consumable);

	RarityType(std::string name, const TCODColor &color, float effectMultiplier, std::vector<std::shared_ptr<RarityEffect>> effects) :
		name(name),
		color(color),
		effectMultiplier(effectMultiplier),
		effects(effects){};
};

