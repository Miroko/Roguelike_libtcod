#pragma once
#include "OperatableObject.h"

class Forge : public OperatableObject
{
public:
	void on();
	std::shared_ptr<OperatableObject> copy();

	Forge(std::string name, Glyph glyph) : OperatableObject(
		name,
		OperatableObject::FORGE,
		9999,
		glyph,
		true){};
};

