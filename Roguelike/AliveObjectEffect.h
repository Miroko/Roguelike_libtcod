#pragma once
#include "DynamicObject.h"
#include <string>
class AliveObjectEffect
{

public:
	int duration;

	std::string name;

	virtual void update(DynamicObject &dynamicObject) = 0;

	AliveObjectEffect(std::string name, int duration) : name(name), duration(duration){};
};
