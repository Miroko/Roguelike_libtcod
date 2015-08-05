#pragma once
#include "Consumable.h"

class Scroll : public Consumable
{
public:
	int value;

	int getValue();
	std::string getStatistics();
	void onConsume(Creature &consumer);

	Scroll(std::string name, Glyph glyph, float weight, int value, RarityType &rarity) :
		Consumable(name, glyph, weight, GameObject::SCROLL, rarity),
		value(value){}
};

