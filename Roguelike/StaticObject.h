#pragma once
#include "GameObject.h"
#include "DynamicObject.h"
#include "memory"

class StaticObject : public GameObject
{

public:
	bool transparent;
	bool raised;

	bool passableBy(DynamicObject &dynamicObject);

	StaticObject(std::string name, Glyph glyph, bool raised = false, bool transparent = true) : raised(raised), transparent(transparent), GameObject(glyph, name){};
	StaticObject(){};
};

const std::shared_ptr<StaticObject> LAND(new StaticObject("Land", Glyph(TCODColor::darkestGreen, TCODColor(5, 20, 5), ' ')));
const std::shared_ptr<StaticObject> TREE(new StaticObject("Tree", Glyph(TCODColor::darkerChartreuse, TCODColor(5, 20, 5), TCOD_CHAR_SPADE), true, false));
const std::shared_ptr<StaticObject> STONE(new StaticObject("Stone", Glyph(TCODColor::darkerGrey, TCODColor::darkerGrey, ' '), true, false));
const std::shared_ptr<StaticObject> STONE_FLOOR(new StaticObject("Stone floor", Glyph(TCODColor::darkestGrey, TCODColor::darkestGrey, ' ')));