#pragma once
#include "Item.h"

class Equipment : public Item
{
private:
	double durabilityMax;
	double durabilityCurrent;

public:
	void durabilityHit(double amount);
	bool isBroken();
	double getDurabilityCurrent();
	double getDurabilityMaxBase();
	double getDurablilityMaxTotal();

	int getValue();
	std::string getStatistics();

	Equipment(Item item, double durability) : 
		Item(item),
		durabilityMax(durability),
		durabilityCurrent(durability){
		durabilityCurrent = getDurablilityMaxTotal();
	}
};

