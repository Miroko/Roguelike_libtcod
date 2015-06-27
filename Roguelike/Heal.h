#pragma once
#include "AliveObjectEffect.h"
class Heal : public AliveObjectEffect
{
public:
	int amount;

	int AliveObjectEffect::getPotency();
	void AliveObjectEffect::apply(DynamicObject &dynamicObject);

	Heal(int amount, int duration) :
		AliveObjectEffect("Heal", duration),
		amount(amount){};
};
