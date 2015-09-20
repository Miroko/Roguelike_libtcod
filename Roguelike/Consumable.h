#pragma once
#include "Item.h"

class Creature;
class CreatureEffect;
class Consumable : public Item
{
public:
	double potency;
	double concentration;

	void onConsume(Creature &consumer);
	int getValue();
	std::string getStatistics();

	Consumable(Item item, double potency, double concentration) :
		Item(item),
		potency(potency),
		concentration(concentration){};
};