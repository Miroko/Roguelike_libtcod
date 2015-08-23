#pragma once
#include "Equipment.h"

class Armor : public Equipment
{
private:
	int defence;

public:
	int limbsRequiredToEquip;

	std::string getStatistics();
	int getValue();
	int getDefence();

	Armor(Equipment equipment, int limbsRequiredToEquip, int defence) :
		Equipment(equipment),
		defence(defence),
		limbsRequiredToEquip(limbsRequiredToEquip){};
};
