#pragma once
#include "Glyph.h"
#include "GameObject.h"
#include <memory>
class Portal : public GameObject
{
public:
	Point2D location;

	static std::shared_ptr<Portal> Portal::newPortal(Portal &portalTemplate);

	Portal(std::string name, Glyph glyph) : GameObject(name, glyph){};
};
