#pragma once
#include "Creature.h"
#include "Weapon.h"
#include "Armor.h"
#include <string>

class RarityEffect
{
public:
	RarityType *rarityAttachedTo; //Set when generated from rarity type

	std::string name;

	virtual void apply(Creature &creature);
	virtual void apply(Weapon &weapon);
	virtual void apply(Armor &armor);

	virtual void applyContinuous(Creature &creature);
	virtual void applyContinuous(Weapon &weapon);
	virtual void applyContinuous(Armor &armor);

	RarityEffect(std::string name) : name(name){};
};

