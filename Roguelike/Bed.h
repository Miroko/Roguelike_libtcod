#pragma once
#include "OperatableObject.h"

class Bed : public OperatableObject
{
public:
	Creature *user;

	bool isInUse();

	void operate(Creature &user) override;
	bool isPassable(DynamicObject &dynamicObject) override;

	std::shared_ptr<OperatableObject> copy();

	Bed(std::string name, Glyph glyph, int health) :
		OperatableObject(OperatableObject(DynamicObject(GameObject(
			name,
			GameObject::BED, 
			glyph),
			health))),
			user(nullptr){}
};

