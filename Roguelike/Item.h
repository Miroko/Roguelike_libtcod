#pragma once
#include "GameObject.h"
class Item : public GameObject
{
public:
	Point2D location;

	enum Type{
		WEAPON,
		CONSUMABLE
	};
	Type type;

	// Kg
	float weight;

	bool operator==(const Item &item);

	Item(Glyph glyph, std::string name, float weight, Type type)
		: GameObject(glyph, name), weight(weight), type(type){};
};

