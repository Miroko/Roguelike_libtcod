#pragma once
#include "GameObject.h"
class Item : public GameObject
{
public:
	// Kg
	float weight;

	Item(Glyph glyph, std::string name, float weight)
		: GameObject(glyph, name), weight(weight){};
};

