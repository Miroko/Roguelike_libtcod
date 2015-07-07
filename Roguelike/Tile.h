#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	bool transparent;
	float walkCost;

	Tile(std::string name, Type type, Glyph glyph, bool transparent, float walkCost) :
		GameObject(name, type, glyph), transparent(transparent), walkCost(walkCost){};
};

