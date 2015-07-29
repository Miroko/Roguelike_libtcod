#pragma once
#include "Consumable.h"

class Potion : public Consumable
{
public:
	int duration;
	int potency;
	std::vector<std::shared_ptr<CreatureEffect>> effects;

	int getValue();
	std::string getStatistics();
	void Consumable::onConsume(Creature &consumer);
	std::shared_ptr<Consumable> newFromClone(RarityType &rarity);

	Potion(std::string name, Glyph glyph, float weight, std::vector<std::shared_ptr<CreatureEffect>> effects, int duration, int potency, Type type, RarityType &rarity) :
		Consumable(name, glyph, weight, type, rarity), effects(effects), duration(duration), potency(potency){};
};

