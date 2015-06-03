#pragma once
#include "GameObject.h"
class Item : public GameObject
{
public:
	enum Type{
		WEAPON,
		CONSUMABLE
	};
	Type type;

	// Kg
	float weight;

	Item(Glyph glyph, std::string name, float weight, Type type)
		: GameObject(glyph, name), weight(weight), type(type){};
};

