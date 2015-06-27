#pragma once
#include "GameObject.h"
#include "DynamicObject.h"
#include <memory>

class StaticObject : public GameObject
{

public:
	bool raised;
	bool transparent;

	StaticObject(std::string name, Glyph glyph, bool raised = false, bool transparent = true) : GameObject(name, glyph), raised(raised), transparent(transparent){};
};