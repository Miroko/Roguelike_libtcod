#pragma once
#include "Item.h"

class Creature;
class Consumable : public Item
{
public:
	void onConsume(Creature &consumer);
	int getValue();

	Consumable(Item item) :
		Item(item){};
};