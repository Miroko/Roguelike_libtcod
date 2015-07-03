#pragma once
#include "OperatableObject.h"

class Door : public OperatableObject
{
public:
	void on();
	void off();
	bool passable(DynamicObject &dynamicObject);
	
	Door(std::string name, Glyph openGlyph, Glyph closedGlyph) :
		OperatableObject(name, GameObject::DOOR ,100, openGlyph, closedGlyph){};
};

