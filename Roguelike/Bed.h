#pragma once
#include "OperatableObject.h"

class Bed : public OperatableObject
{
public:
	bool passable(DynamicObject &dynamicObject);

	std::shared_ptr<OperatableObject> copy();

	Bed(std::string name, Glyph glyph, int health) :
		OperatableObject(OperatableObject(DynamicObject(GameObject(
			name,
			GameObject::BED, 
			glyph),
			health))){}
};

