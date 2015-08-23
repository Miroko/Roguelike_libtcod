#pragma once
#include "Item.h"

class Equipment : public Item
{
public:
	double durabilityMax;
	double durabilityCurrent;

	void durabilityHit(double amount);
	bool isBroken();

	std::string getStatistics();

	Equipment(Item item, double durability) : 
		Item(item),
		durabilityMax(durability),
		durabilityCurrent(durability){}
};

