#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(std::string name, Type type, Glyph glyph) :
		GameObject(name, type, glyph){};
};

