#pragma once
#include "StaticObject.h"
class Portal : public StaticObject
{
public:
	Point2D location;

	static std::shared_ptr<Portal> Portal::newPortal(const Portal &portalTemplate);

	Portal(std::string name, Glyph glyph) : StaticObject(name, glyph){};
};

const Portal FOREST_PORTAL = Portal("Exit", Glyph(TCODColor::lightGreen, LAND->glyph.bgColor, '>'));
const Portal CAVE_PORTAL = Portal("Exit", Glyph(TCODColor::lightGrey, STONE_FLOOR->glyph.bgColor, '>'));