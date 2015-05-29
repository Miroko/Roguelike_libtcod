#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "Glyph.h"
#include "string"
class GameObject
{
private:

public:
	Glyph glyph;
	std::string name;
	void render(int x, int y);	
	GameObject(Glyph glyph, std::string name) : glyph(glyph), name(name){};
	GameObject(){};
};

