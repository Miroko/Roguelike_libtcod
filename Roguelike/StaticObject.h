#pragma once
#include "GameObject.h"
#include "DynamicObject.h"
#include "memory"

class StaticObject : public GameObject
{

public:
	bool isTransparent;
	virtual bool isPassableBy(DynamicObject &dynamicObject);

	StaticObject(Glyph glyph, std::string name, bool isTransparent = false) : GameObject(glyph, name), isTransparent(isTransparent){};
	StaticObject(){};
};

class Land : public StaticObject{
public:
	bool isPassableBy(DynamicObject &dynamicObject);

	Land() : StaticObject(Glyph(TCODColor::darkestGreen, TCODColor(5, 20, 5), ' '), "Land", true){};
};

class Tree : public StaticObject{
public:
	Tree() : StaticObject(Glyph(TCODColor::darkerChartreuse, TCODColor(5, 20, 5), TCOD_CHAR_SPADE), "Tree"){};
};

class Stone : public StaticObject{
public:
	Stone() : StaticObject(Glyph(TCODColor::darkerGrey, TCODColor::darkerGrey, ' '), "Stone"){};
};

class StoneFloor : public StaticObject{
public:
	bool isPassableBy(DynamicObject &dynamicObject);

	StoneFloor() : StaticObject(Glyph(TCODColor::darkestGrey, TCODColor::darkestGrey, ' '), "Stone floor", true){};
};


static std::shared_ptr<StaticObject> LAND(new Land());
static std::shared_ptr<StaticObject> TREE(new Tree());
static std::shared_ptr<StaticObject> STONE(new Stone());
static std::shared_ptr<StaticObject> STONE_FLOOR(new StoneFloor());