#pragma once
#include "Item.h"

class Armor : public Item
{
private:
	int defence;

public:
	int limbsRequiredToEquip;

	std::string getStatistics();
	int getValue();
	int getDefence();

	Armor(Item item, int limbsRequiredToEquip, int defence) :
		Item(item),
		defence(defence),
		limbsRequiredToEquip(limbsRequiredToEquip){};
};
