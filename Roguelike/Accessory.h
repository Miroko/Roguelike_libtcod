#pragma once
#include "Equipment.h"

class Accessory : public Item
{
private:
	double spellPower;

public:
	int getValue();
	std::string getStatistics();

	double getSpellPowerBase();
	double getSpellPowerTotal();

	Accessory(Item item, double spellPower) : 
		Item(item),
		spellPower(spellPower){
	}
};
