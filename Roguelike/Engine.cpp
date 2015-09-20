#include "Engine.h"
#include "QuestTheGoblinKing.h"

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

//magic
double engine::magicMax;
double engine::magicCostBase;
double engine::magicStaminaCostPerMagic;
double engine::magicSpellPowerMax;

//damage
double engine::damageMax;

//defence
double engine::defenceMax;

//weight
double engine::weightCarryMax;
double engine::weightDamagePerKg;

//accuracy
double engine::accuracyBasePercentage;

//durability
double engine::durabilityMax;
double engine::durabilityBaseCost;
double engine::durabilityMaxEffectOnDamagePercentage;
double engine::durabilityMaxEffectOnDefencePercentage;

//stamina
double engine::staminaMax;
double engine::staminaBaseRegen;
double engine::staminaBaseWaitRegen;
double engine::staminaCostPerKgFromMove;
double engine::staminaCostPerKgFromAttack;
double engine::staminaCostFromDamageRation;

//effect
double engine::effectDurationBase;

//value
double engine::valueBase;
double engine::valuePerKg;
double engine::valuePerStamina;
double engine::valuePerHealth;
double engine::valuePerMagic;
double engine::valuePerDamage;
double engine::valuePerDefence;
double engine::valuePerSpellPower;

//loot
double engine::statisticVariation;
double engine::lootMinPrevalenceMultiplier;
double engine::lootRollDropChance;
int engine::lootDropRolls;

//consumable
double engine::consumablePotencyMax;
double engine::consumableConcentrationMax;

void engine::init(){
	TCODConsole::initRoot(160, 80, "Roguelike", false, TCOD_RENDERER_OPENGL);
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(60, 20);

	//health
	healthMax = 1000; // 1000

	//magic
	magicMax = 1000;
	magicCostBase = magicMax / 1.5;
	magicStaminaCostPerMagic = magicMax / 1000 * 2.5;
	magicSpellPowerMax = 1.0;

	//damage
	damageMax = healthMax / 10;

	//defence
	defenceMax = healthMax / 20; // 40

	//weight
	weightCarryMax = 50.0; // 50
	weightDamagePerKg = (damageMax / weightCarryMax) * 0.25;

	//accuracy
	accuracyBasePercentage = 1.0;

	//durability
	durabilityMax = 300;
	durabilityBaseCost = 1;
	durabilityMaxEffectOnDamagePercentage = 0.90;
	durabilityMaxEffectOnDefencePercentage = 0.90;

	//stamina
	staminaMax = 1000; // 1000
	staminaBaseRegen = staminaMax / weightCarryMax; // 20
	staminaBaseWaitRegen = staminaBaseRegen * 2; // 40
	staminaCostPerKgFromMove = (staminaBaseRegen * 2) / weightCarryMax; //stamina regen per turn == | -20 when carrying 50kg | +20 when carrying 0kg |
	staminaCostPerKgFromAttack = (staminaMax / weightCarryMax) / 4;
	staminaCostFromDamageRation = 0.7;

	//effect
	effectDurationBase = 10.0;

	//value
	valueBase = 300;
	valuePerKg = valueBase / weightCarryMax / 2.0;
	valuePerStamina = valueBase / staminaMax / 2.5;
	valuePerHealth = valueBase / healthMax;
	valuePerDamage = valueBase / damageMax / 2.0;
	valuePerDefence = valueBase / defenceMax / 1.5;
	valuePerMagic = valueBase * 8 / magicMax;
	valuePerSpellPower = valuePerMagic * 3;

	//loot
	statisticVariation = 0.20;
	lootMinPrevalenceMultiplier = 0.30;
	lootRollDropChance = 1.00;
	lootDropRolls = 6;

	//consumable
	consumablePotencyMax = 1.0;
	consumableConcentrationMax = 1.0;

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
	playerHandler.getPlayerCreature()->inventory.currency = (int)valueBase;

	//Quest
	std::shared_ptr<Quest> quest = std::shared_ptr<Quest>(new QuestTheGoblinKing());
	questHandler.setCurrentQuest(quest);
	questHandler.travelToVillage();
}