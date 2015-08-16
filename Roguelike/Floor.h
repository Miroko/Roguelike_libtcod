#pragma once
#include "Tile.h"

class Floor : public Tile
{
public:
	Floor(std::string name, Glyph glyph, double walkCost = 10.0f) :
		Tile(GameObject(
		name, 
		GameObject::FLOOR, 
		glyph),
		true, 
		walkCost){}
};

