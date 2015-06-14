#pragma once
#include "StaticObject.h"
class Portal : public StaticObject
{
public:
	Point2D location;

	static std::shared_ptr<Portal> Portal::newPortal(const Portal &portalTemplate);

	Portal(std::string name, Glyph glyph) : StaticObject(name, glyph){};
};

const Portal FOREST_PORTAL = Portal("Forest entrance", Glyph(TCODColor::lightGreen, LAND->glyph.bgColor, '>'));
const Portal CAVE_PORTAL = Portal("Cave entrance", Glyph(TCODColor::lightGrey, STONE_WALL_FLOOR->glyph.bgColor, '>'));
