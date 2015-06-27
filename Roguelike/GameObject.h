#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "Glyph.h"
#include <string>
class GameObject
{
private:

public:
	Glyph glyph;
	std::string name;

	virtual void render(int x, int y);
	virtual std::string getDescription();

	GameObject(std::string name, Glyph glyph) : glyph(glyph), name(name){};
};

