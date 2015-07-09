#pragma once
#include "OperatableObject.h"

class Bed : public OperatableObject
{
public:
	bool passable(DynamicObject &dynamicObject);

	std::shared_ptr<OperatableObject> copy();

	Bed(std::string name, Glyph glyph) : OperatableObject(
		name,
		GameObject::BED, 
		100, 
		glyph,
		true){};
};

