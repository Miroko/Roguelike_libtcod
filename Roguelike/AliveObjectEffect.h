#pragma once
#include "DynamicObject.h"
#include <string>
class AliveObjectEffect
{

public:
	template <typename T> static std::shared_ptr<T> newEffect(const std::shared_ptr<T> &effectTemplate){
		std::shared_ptr<T> effect = std::shared_ptr<T>(new T(*effectTemplate));
		return effect;
	}

	enum Type{
		HEAL
	};
	Type type;

	int duration;

	std::string name;

	virtual int getPotency() = 0;

	virtual void update(DynamicObject &dynamicObject) = 0;

	AliveObjectEffect(std::string name, int duration, Type type) : name(name), duration(duration), type(type){};
};

