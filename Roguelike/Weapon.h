#pragma once
#include "Equipment.h"

class CreatureSkill;
class Weapon : public Equipment
{
private:
	int damage;

public:
	CreatureSkill &skillUsed;

	std::string getStatistics();
	int getValue();
	int getDamageBase();
	int getDamageTotal();
	double getAccuracyModifier();
	double getStaminaCostModifier();

	Weapon(Equipment equipment, int damage, CreatureSkill &skillUsed) :
		Equipment(equipment),
		damage(damage),
		skillUsed(skillUsed){};
};

