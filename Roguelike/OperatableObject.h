#pragma once
#include "DynamicObject.h"

class OperatableObject : public DynamicObject
{
public:
	bool isOn = false;

	virtual void on();
	virtual void off();

	virtual bool passable(DynamicObject &dynamicObject);

	void onTakeDamageEffect();
	void messageDeath();

	virtual std::shared_ptr<OperatableObject> copy();

	OperatableObject(std::string name, Type type, int health, Glyph glyph, bool transparent) :
		DynamicObject(name, type, glyph, health, transparent){}
};
