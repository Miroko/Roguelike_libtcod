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

	extern int healthMax;
	extern int damageMax;
	extern int defenceMax;
	extern float carryWeightMax;
	extern int staminaBaseRegen;
	extern int staminaBaseWaitRegen;
	extern float staminaCostPerKgFromMove;
	extern float staminaCostPerKgFromAttack;
	extern float staminaCostFromDamageRation;
	extern float valueVariation;
	extern float lootRarityFromCreatureRarityRatio;
	extern float lootRollMissChance;
	extern int lootDropRolls;

	extern void init();
	extern void newGame();
}
