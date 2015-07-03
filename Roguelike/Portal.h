#pragma once
#include "Tile.h"

class Portal : public Tile
{
public:
	Portal(std::string name, Glyph glyph) : Tile(name, GameObject::PORTAL, glyph){};
};
