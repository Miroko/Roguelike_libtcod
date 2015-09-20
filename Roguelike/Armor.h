#pragma once
#include "Equipment.h"

class Armor : public Equipment
{
private:
	int defence;

public:
	int limbsRequiredToEquip;

	int getDefenceBase();
	int getDefenceTotal();

	std::string getStatistics();
	int getValue();

	Armor(Equipment equipment, int limbsRequiredToEquip, int defence) :
		Equipment(equipment),
		defence(defence),
		limbsRequiredToEquip(limbsRequiredToEquip){};
};
