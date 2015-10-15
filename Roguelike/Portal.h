#pragma once
#include "Tile.h"

class Portal : public Tile
{
public:
	Portal(std::string name, Glyph glyph) :
		Tile(GameObject(
		name, 
		GameObject::PORTAL, 
		glyph)){}
};

