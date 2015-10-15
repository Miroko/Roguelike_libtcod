#pragma once
#include "Tile.h"

class Floor : public Tile
{
public:
	Floor(std::string name, Glyph glyph, int movementCost = 10) :
		Tile(GameObject(
		name, 
		GameObject::FLOOR, 
		glyph),
		movementCost){}
};

