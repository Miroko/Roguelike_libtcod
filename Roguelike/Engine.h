#pragma once
#include "Camera.h"
#include "PlayerHandler.h"
#include "QuestHandler.h"
#include "Area.h"
class Engine
{

private:
	void render();
	void update(TCOD_key_t key, float elapsed);
public:
	static Camera camera;
	static PlayerHandler playerHandler;
	static QuestHandler questHandler;
	static Area area;

	void start();

	Engine(){};
};