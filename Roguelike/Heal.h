#pragma once
#include "AliveObjectEffect.h"
class Heal : public AliveObjectEffect
{
public:
	int amount;

	void update(DynamicObject &dynamicObject);

	Heal(int amount, int duration) : AliveObjectEffect("Heal", duration), amount(amount){};
};

const std::shared_ptr<Heal> HEAL = std::shared_ptr<Heal>(new Heal(1,5));
