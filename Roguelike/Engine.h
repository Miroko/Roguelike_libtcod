#pragma once
#include "Camera.h"
#include "QuestHandler.h"
#include "Gui.h"
#include "VisualEffectHandler.h"
#include "AreaHandler.h"
#include "PlayerHandler.h"
#include "Random.h"
#include "String.h"
#include "RaritySystem.h"
#include "ObjectLibrary.h"
#include "ObjectFactory.h"

namespace engine{
	extern String string;
	extern Random random;
	extern RaritySystem raritySystem;
	extern ObjectLibrary objectLibrary;
	extern ObjectFactory objectFactory;
	extern Camera camera;
	extern PlayerHandler playerHandler;
	extern AreaHandler areaHandler;
	extern QuestHandler questHandler;
	extern VisualEffectHandler visualEffectHandler;
	extern Gui gui;
	extern bool requestUpdate;

	//health
	extern double healthMax;

	//damage
	extern double damageMax;

	//defence
	extern double defenceMax;

	//weight
	extern double carryWeightMax;

	//accuracy
	extern double accuracyBasePercentage;

	//durability
	extern double durabilityMax;
	extern double durabilityBaseCost;
	extern double durabilityMaxEffectOnDamagePercentage;
	extern double durabilityMaxEffectOnDefencePercentage;

	//stamina
	extern double staminaMax;
	extern double staminaBaseRegen;
	extern double staminaBaseWaitRegen;
	extern double staminaCostPerKgFromMove;
	extern double staminaCostPerKgFromAttack;
	extern double staminaCostFromDamageRation;

	//value
	extern double valueBase;
	extern double valuePerKg;
	extern double valuePerStamina;
	extern double valuePerHealth;
	extern double valuePerDamage;
	extern double valuePerDefence;

	//loot
	extern double statisticVariation;
	extern double lootRarityFromCreatureRarityRatio;
	extern double lootRollDropChance;
	extern int lootDropRolls;

	extern void init();
	extern void newGame();
}
