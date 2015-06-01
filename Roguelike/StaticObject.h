#pragma once
#include "GameObject.h"
#include "DynamicObject.h"
#include "memory"

class StaticObject : public GameObject
{

public:
	bool isTransparent;
	virtual bool isPassableBy(DynamicObject &dynamicObject) = 0;

	StaticObject(Glyph glyph, std::string name, bool isTransparent = false) : GameObject(glyph, name), isTransparent(isTransparent){};
	StaticObject(){};
};

class Land : public StaticObject{
public:
	bool StaticObject::isPassableBy(DynamicObject &dynamicObject);

	Land() : StaticObject(Glyph(TCODColor::darkestGreen, TCODColor(5, 20, 5), ' '), "Land", true){};
};

class Wall : public StaticObject{
public:
	bool StaticObject::isPassableBy(DynamicObject &dynamicObject);

	Wall() : StaticObject(Glyph(TCODColor::darkGrey, TCODColor::darkGrey, ' '), "Wall"){};
};

class Tree : public StaticObject{
public:
	bool StaticObject::isPassableBy(DynamicObject &dynamicObject);

	Tree() : StaticObject(Glyph(TCODColor::darkerChartreuse, TCODColor(5, 20, 5), TCOD_CHAR_SPADE), "Tree"){};
};

static std::shared_ptr<StaticObject> LAND(new Land());
static std::shared_ptr<StaticObject> WALL(new Wall());
static std::shared_ptr<StaticObject> TREE(new Tree());