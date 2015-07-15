#pragma once
#include "Camera.h"
#include "QuestHandler.h"
#include "Gui.h"
#include "VisualEffectHandler.h"
#include "AreaHandler.h"
#include "PlayerHandler.h"
#include "Random.h"
#include "String.h"
#include "ObjectLibrary.h"
#include "ObjectFactory.h"

namespace engine{
	extern String string;
	extern Random random;
	extern ObjectLibrary objectLibrary;
	extern ObjectFactory objectFactory;
	extern Camera camera;
	extern PlayerHandler playerHandler;
	extern AreaHandler areaHandler;
	extern QuestHandler questHandler;
	extern VisualEffectHandler visualEffectHandler;
	extern Gui gui;

	extern bool requestUpdate;

	extern void init();
	extern void newGame();
}
