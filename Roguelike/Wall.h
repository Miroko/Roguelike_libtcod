#pragma once
#include "Tile.h"

class Wall : public Tile
{
public:
	Wall(std::string name, Glyph glyph) : 
		Tile(GameObject(
		name, 
		GameObject::WALL, 
		glyph), 
		false, 
		0.0f){}
};

