#pragma once
#include "AliveObjectEffect.h"
class Heal : public AliveObjectEffect
{
public:
	int amount;

	int AliveObjectEffect::getPotency();

	void update(DynamicObject &dynamicObject);

	Heal(int amount, int duration) : AliveObjectEffect("Heal", duration, AliveObjectEffect::HEAL), amount(amount){};
};

const std::shared_ptr<Heal> HEAL = std::shared_ptr<Heal>(new Heal(1,5));
