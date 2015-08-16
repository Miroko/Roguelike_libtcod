#pragma once
#include "OperatableObject.h"

class Forge : public OperatableObject
{
public:
	void on();
	std::shared_ptr<OperatableObject> copy();

	Forge() :
		OperatableObject(DynamicObject(GameObject(
		"Forge", 
		GameObject::FORGE, 
		Glyph(TCODColor::darkerGrey, TCODColor::darkRed, 'F')),
		9999)){}
};

