#include "Engine.h"
#include "QuestTheGoblinKing.h"
#include "AiNone.h"

String engine::string;
Random engine::random;
RaritySystem engine::raritySystem;
ObjectLibrary engine::objectLibrary;
ObjectFactory engine::objectFactory;
Camera engine::camera;
PlayerHandler engine::playerHandler;
AreaHandler engine::areaHandler;
QuestHandler engine::questHandler;
VisualEffectHandler engine::visualEffectHandler;
Gui engine::gui;
bool engine::requestUpdate = false;

//health
double engine::healthMax;

//damage
double engine::damageMax;

//defence
double engine::defenceMax;

//weight
double engine::carryWeightMax;

//stamina
double engine::staminaMax;
double engine::staminaBaseRegen;
double engine::staminaBaseWaitRegen;
double engine::staminaCostPerKgFromMove;
double engine::staminaCostPerKgFromAttack;
double engine::staminaCostFromDamageRation;

//value
double engine::valueBase;
double engine::valuePerKg;
double engine::valuePerStamina;
double engine::valuePerHealth;
double engine::valuePerDamage;
double engine::valuePerDefence;

//loot
double engine::statisticVariation;
double engine::lootRarityFromCreatureRarityRatio;
double engine::lootRollDropChance;
int engine::lootDropRolls;

void engine::init(){
	TCODConsole::initRoot(160, 80, "Roguelike", false, TCOD_RENDERER_OPENGL);
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(60, 20);

	//health
	healthMax = 1000; // 1000

	//damage
	damageMax = healthMax / 25; // 40

	//defence
	defenceMax = healthMax / 25; // 40

	//weight
	carryWeightMax = 50.0f; // 50

	//stamina
	staminaMax = 1000; // 1000
	staminaBaseRegen = staminaMax / carryWeightMax; // 20
	staminaBaseWaitRegen = staminaBaseRegen * 2; // 40
	staminaCostPerKgFromMove = (staminaBaseRegen * 2) / carryWeightMax; //stamina regen per turn == | -20 when carrying 50kg | +20 when carrying 0kg |
	staminaCostPerKgFromAttack = staminaMax / carryWeightMax / 2; // 10 per kg == cost 500 when weapon weight == 50kg
	staminaCostFromDamageRation = 0.7f;

	//value
	valueBase = 300;
	valuePerKg = valueBase / carryWeightMax;
	valuePerStamina = valueBase / staminaMax / 2.5f;
	valuePerHealth = valueBase / healthMax;
	valuePerDamage = valueBase / damageMax / 2.0f;
	valuePerDefence = valueBase / defenceMax / 1.5f;

	//loot
	statisticVariation = 0.20f;
	lootRarityFromCreatureRarityRatio = 0.80f;
	lootRollDropChance = 0.30f;
	lootDropRolls = 6;

	objectLibrary.init();
	raritySystem.init();
	random.init();
	gui.init();

	newGame();

	//Main loop
	while (!TCODConsole::isWindowClosed()){
		TCODConsole::root->clear();
		TCOD_key_t keyPressed = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
		if (keyPressed.vk != TCODK_NONE){
			if (!gui.handleKey(keyPressed)){
				if (playerHandler.playerController.handleKey(keyPressed)){
					requestUpdate = true;
				}
			}
			if (requestUpdate){
				areaHandler.updateArea();
				gui.update();
				camera.centerOn(playerHandler.getPlayerCreature()->location);
				requestUpdate = false;
			}
		}
		areaHandler.renderArea();
		visualEffectHandler.render();
		gui.render();
		TCODConsole::root->flush();
	}
}
void engine::newGame(){
	//reset visual effects
	visualEffectHandler.runningEffects.clear();

	//reset saved data
	areaHandler.savedPhaseAreas.clear();

	//Player
	playerHandler.setPlayerCreature(objectFactory.createCreature("player", "common"));
	playerHandler.getPlayerCreature()->inventory.currency = valueBase;

	//Quest
	std::shared_ptr<Quest> quest = std::shared_ptr<Quest>(new QuestTheGoblinKing());
	questHandler.setCurrentQuest(quest);
	questHandler.travelToVillage();
}