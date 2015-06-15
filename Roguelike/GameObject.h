#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "Glyph.h"
#include <string>
class DynamicObject;
class GameObject
{
private:

public:
	Glyph glyph;
	std::string name;

	bool transparent;

	virtual bool passable();
	virtual void render(int x, int y);
	virtual std::string getDescription();

	GameObject(Glyph glyph, std::string name, bool transparent) : glyph(glyph), name(name), transparent(transparent){};
	GameObject(){};
};

