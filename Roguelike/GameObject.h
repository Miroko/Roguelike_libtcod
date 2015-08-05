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
		WATER,

		CREATURE,
		
		DOOR,
		BED,
		FORGE,
		ANVIL,
		ALCHEMY_TABLE,

		WEAPON_MELEE,
		WEAPON_RANGED,
		ARMOR_HEAD,
		ARMOR_BODY,
		ARMOR_HAND,
		ARMOR_LEG,

		POTION,
		SCROLL
	};
	Type type;
	std::string name;
	Glyph glyph;

	bool isWeapon();
	bool isArmor();
	bool isConsumable();
	bool isOperatable();
	bool isTile();

	Type getType();
	virtual void render(int x, int y);
	virtual std::string getDescription();

	GameObject(std::string name, Type type, Glyph glyph) :
		name(name), type(type), glyph(glyph){};
};

