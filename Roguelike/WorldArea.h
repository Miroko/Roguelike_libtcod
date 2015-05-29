#pragma once
#include "Rectangle.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "vector"
#include "memory"

class WorldArea
{
public:
	Rectangle bounds;

	std::vector<std::vector<std::shared_ptr<StaticObject>>> staticObjects;
	std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;

	WorldArea(int size);
	WorldArea(){};
};

