#pragma once
#include "Camera.h"
#include "PlayerHandler.h"
#include "QuestHandler.h"
#include "Area.h"
#include "Inventory.h"
#include "Log.h"
#include "Human.h"
#include "ClearCave.h"
class Engine
{

private:
	void render();
	void updateSimulation();
	void updateGraphics(float elapsed);
	bool handleInput(TCOD_key_t key);
public:
	static Camera camera;
	static PlayerHandler playerHandler;
	static QuestHandler questHandler;
	static Area area;

	static Inventory inventory;
	static Log log;

	void start();

	Engine(){};
};