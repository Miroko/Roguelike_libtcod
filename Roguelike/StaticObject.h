#pragma once
#include "GameObject.h"
#include "DynamicObject.h"
#include "memory"

class StaticObject : public GameObject
{
	
public:

	virtual bool isPassableBy(DynamicObject &dynamicObject) = 0;

	StaticObject(Glyph glyph, std::string name) : GameObject(glyph, name){};
	StaticObject(){};
};

class Land : public StaticObject{
public:
	bool StaticObject::isPassableBy(DynamicObject &dynamicObject);

	Land() : StaticObject(Glyph(TCODColor::darkestGreen, TCODColor::darkestGreen, ' '), "Land"){};
};

class Wall : public StaticObject{
public:
	bool StaticObject::isPassableBy(DynamicObject &dynamicObject);

	Wall() : StaticObject(Glyph(TCODColor::darkGrey, TCODColor::darkGrey, ' '), "Wall"){};
};

const std::shared_ptr<Land> LAND = std::shared_ptr<Land>(new Land());
const std::shared_ptr<Wall> WALL = std::shared_ptr<Wall>(new Wall());