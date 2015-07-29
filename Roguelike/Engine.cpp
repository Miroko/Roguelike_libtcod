#include "Engine.h"
#include "QuestTheGoblinKing.h"
#include "AiNone.h"

String engine::string;
Random engine::random;
ObjectLibrary engine::objectLibrary;
ObjectFactory engine::objectFactory;
Camera engine::camera;
PlayerHandler engine::playerHandler;
AreaHandler engine::areaHandler;
QuestHandler engine::questHandler;
VisualEffectHandler engine::visualEffectHandler;
Gui engine::gui;
bool engine::requestUpdate = false;

void engine::init(){
	TCODConsole::initRoot(120, 60, "Roguelike", false, TCOD_RENDERER_SDL);
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(60, 20);

	random.init();
	objectLibrary.init();
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
	std::shared_ptr<Creature> playerCreature = objectFactory.createCreaturePreset("player", *engine::objectLibrary.getRarity("rarity_common"));
	playerHandler.setPlayerCreature(playerCreature);
	playerHandler.playerInventory.currency = 50;

	//Quest
	std::shared_ptr<Quest> quest = std::shared_ptr<Quest>(new QuestTheGoblinKing());
	questHandler.setCurrentQuest(quest);
	questHandler.travelToVillage();
}