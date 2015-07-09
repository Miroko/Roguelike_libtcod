#pragma once
#include "OperatableObject.h"

class Anvil : public OperatableObject
{
public:
	void on();
	std::shared_ptr<OperatableObject> copy();

	Anvil(std::string name, Glyph glyph) : OperatableObject(
		name,
		OperatableObject::ANVIL,
		9999,
		glyph,
		true){}
};

