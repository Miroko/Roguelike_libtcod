#pragma once
#include "Camera.h"
#include "QuestHandler.h"
#include "Gui.h"
#include "VisualEffectPlayer.h"
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
	extern VisualEffectPlayer visualEffectPlayer;
	extern Gui gui;
	extern bool requestUpdate;

	//render
	extern int renderItemsRate;
	extern bool renderWithoutFov;

	//health
	extern double healthMax;

	//magic
	extern double magicMax; //base magic in creatures
	extern double magicCostBase;
	extern double magicStaminaCostPerMagic;
	extern double magicSpellPowerMax; //spell effectivity in accessories

	//damage
	extern double damageMax;

	//defence
	extern double defenceMax;

	//weight
	extern double weightCarryMax;
	extern double weightDamagePerKg;

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

	//effect
	extern double effectDurationBase;

	//value
	extern double valueBase;
	extern double valuePerKg;
	extern double valuePerStamina;
	extern double valuePerHealth;
	extern double valuePerMagic;
	extern double valuePerSpellPower;
	extern double valuePerDamage;
	extern double valuePerDefence;

	//loot
	extern double statisticVariation;
	extern double lootMinPrevalenceMultiplier;
	extern double lootRollDropChance;
	extern int lootDropRollsBase;

	//consumable
	extern double consumablePotencyMax;
	extern double consumableConcentrationMax;

	extern void init();
	extern void newGame();
}
