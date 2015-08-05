#pragma once
#include "Consumable.h"

class Potion : public Consumable
{
public:
	int value;
	std::vector<std::shared_ptr<CreatureEffect>> effects;

	int getValue();
	std::string getStatistics();
	void Consumable::onConsume(Creature &consumer);

	Potion(std::string name, Glyph glyph, float weight, std::vector<std::shared_ptr<CreatureEffect>> effects, int value, Type type, RarityType &rarity) :
		Consumable(name, glyph, weight, type, rarity),
		effects(effects), 
		value(value){};
};
