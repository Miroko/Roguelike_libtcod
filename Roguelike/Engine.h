#pragma once
#include "Camera.h"
#include "PlayerHandler.h"
#include "QuestHandler.h"
#include "Area.h"
#include "Inventory.h"
#include "Log.h"
#include "human.h"
#include "Gui.h"
#include "ClearCave.h"
class Engine
{

private:
	void renderSimulation();
	void updateSimulation();
	void renderRealTime(float elapsed);
	bool handleInput(TCOD_key_t key);
public:
	static Camera camera;
	static PlayerHandler playerHandler;
	static QuestHandler questHandler;
	static Area area;

	static Gui GUI;

	void start();

	Engine(){};
};