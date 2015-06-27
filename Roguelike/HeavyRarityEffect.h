#pragma once
#include "RarityEffect.h"

class HeavyRarityEffect : public RarityEffect
{
private:
	const float MULTIPLIER_MIN = 1.3;
	const float MULTIPLIER_MAX = 1.6;

public:
	virtual void apply(Creature &creature);
	virtual void apply(Weapon &weapon);
	virtual void apply(Armor &armor);

	virtual void applyContinuous(Creature &creature);
	virtual void applyContinuous(Weapon &weapon);
	virtual void applyContinuous(Armor &armor);

	HeavyRarityEffect() : RarityEffect("Heavy"){};
};

