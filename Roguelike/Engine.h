#pragma once
#include "Camera.h"
#include "PlayerController.h"
#include "QuestHandler.h"
#include "Area.h"
#include "human.h"
#include "Gui.h"
#include "TheGoblinKing.h"
class Engine
{

private:
	void renderSimulation();
	void updateSimulation();
	void renderRealTime(float elapsed);
	bool handleInput(TCOD_key_t key);
public:
	static Camera camera;
	static PlayerController playerController;
	static QuestHandler questHandler;
	static Area area;

	static Gui GUI;

	void start();

	Engine(){};
};