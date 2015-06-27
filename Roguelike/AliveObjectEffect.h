#pragma once
#include "DynamicObject.h"
#include <string>

class AliveObjectEffect
{

public:
	std::string name;
	int duration;

	virtual int getPotency() = 0;
	virtual void apply(DynamicObject &dynamicObject) = 0;

	AliveObjectEffect(std::string name, int duration) : name(name), duration(duration){};
};

