#pragma once
#include "Tile.h"

class Water : public Tile
{
public:
	Water(std::string name, Glyph glyph) :
		Tile(GameObject(
		name, 
		GameObject::WATER, 
		glyph),
		true, 
		20.0f){}
};

