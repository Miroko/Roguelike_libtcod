#pragma once
#include "OperatableObject.h"

class Anvil : public OperatableObject
{
public:
	void on();
	std::shared_ptr<OperatableObject> copy();

	Anvil() :
		OperatableObject(DynamicObject(GameObject(
		"Anvil",
		GameObject::ANVIL, 
		Glyph(TCODColor::darkerGrey, TCODColor::darkGrey, 'A')),
		9999)){}
};

