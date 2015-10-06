#pragma once
#include "OperatableObject.h"

class Door : public OperatableObject
{
public:
	bool isOpen;

	Glyph openGlyph;
	Glyph closedGlyph;

	void operate(Creature &user) override;
	bool isPassable(DynamicObject &dynamicObject) override;

	std::shared_ptr<OperatableObject> copy();
	
	Door(std::string name, Glyph open, Glyph closed, int health) :
		OperatableObject(DynamicObject(GameObject(
		name,
		GameObject::DOOR,
		closed),
		health)),
		openGlyph(open),
		closedGlyph(closed),
		isOpen(false){};
};

