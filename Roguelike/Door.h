#pragma once
#include "OperatableObject.h"

class Door : public OperatableObject
{
public:
	bool isOpen;

	Glyph onGlyph;
	Glyph offGlyph;

	void operate(Creature &user) override;
	bool isPassable(DynamicObject &dynamicObject) override;

	std::shared_ptr<OperatableObject> copy();
	
	Door(std::string name, Glyph open, Glyph closed, int health) :
		OperatableObject(DynamicObject(GameObject(
		name,
		GameObject::DOOR,
		closed),
		health,
		false)),
		onGlyph(open),
		offGlyph(closed),
		isOpen(false){};
};

