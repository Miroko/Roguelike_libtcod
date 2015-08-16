#pragma once
#include "OperatableObject.h"

class AlchemyTable : public OperatableObject
{
public:
	void on();
	std::shared_ptr<OperatableObject> copy();

	AlchemyTable(std::string name, Glyph glyph) :
		OperatableObject(DynamicObject(GameObject(
		name,
		GameObject::ALCHEMY_TABLE,
		glyph),
		100)){}
};

