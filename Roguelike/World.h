#pragma once
#include "libtcod.hpp"
#include "WorldArea.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Camera.h"
#include "memory"
class World
{
private:
	
public:

	WorldArea area;

	std::shared_ptr<DynamicObject> playerObject = nullptr;
	
	bool moveDynamicObject(DynamicObject &dynamicObject, Point2D &toLocation);
	
	void placePlayer(DynamicObject &playerObject);

	void update(float elapsed);	

	World();
	
};

