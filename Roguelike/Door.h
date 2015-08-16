#pragma once
#include "OperatableObject.h"

class Door : public OperatableObject
{
public:
	Glyph onGlyph;
	Glyph offGlyph;

	void on();
	void off();
	bool passable(DynamicObject &dynamicObject);

	void render(int x, int y);

	std::shared_ptr<OperatableObject> copy();
	
	Door(std::string name, Glyph open, Glyph closed, int health) :
		OperatableObject(DynamicObject(GameObject(
		name,
		GameObject::DOOR,
		open),
		health,
		false)),
		onGlyph(open),
		offGlyph(closed){};
};

