#pragma once
#include "DynamicObject.h"

class OperatableObject : public DynamicObject
{
public:
	bool isOn = false;

	Glyph onGlyph;
	Glyph offGlyph;

	virtual void on();
	virtual void off();

	virtual bool passable(DynamicObject &dynamicObject);

	void onTakeDamageEffect();
	void messageDeath();

	void render(int x, int y);

	OperatableObject(std::string name, Type type, int health, Glyph onGlyph, Glyph offGlyph) :
		DynamicObject(name, type, offGlyph, health, false),
		onGlyph(onGlyph),
		offGlyph(offGlyph){};
};
