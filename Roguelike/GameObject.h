#pragma once
#include "libtcod.hpp"
#include "Point2D.h"
#include "Glyph.h"
#include <string>

class GameObject
{
private:

public:	
	enum Type{
		FLOOR,
		WALL,
		PORTAL,
		CREATURE,
		DOOR,
		WEAPON_MELEE,
		WEAPON_RANGED,
		ARMOR_HEAD,
		ARMOR_BODY,
		ARMOR_HAND,
		ARMOR_LEG,
		CONSUMABLE
	};
	Type type;
	std::string name;
	Glyph glyph;

	Type getType();
	virtual void render(int x, int y);
	virtual std::string getDescription();

	GameObject(std::string name, Type type, Glyph glyph) :
		name(name), type(type), glyph(glyph){};
};

