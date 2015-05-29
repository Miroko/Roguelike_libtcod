#pragma once
#include "World.h"
#include "Camera.h"
class Engine
{

private:
	World world;
	Camera camera;
	
	void render();
	void update(TCOD_key_t key, float elapsed);
public:
	
	void startMainLoop();

	Engine(){};
};

