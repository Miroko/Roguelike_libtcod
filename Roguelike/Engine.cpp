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
	TCODConsole::setKeyboardRepeat(20, 20);

	random.init();
	objectLibrary.init();
	gui.init();

	//Player
	std::shared_ptr<Creature> playerCreature = objectFactory.createCreaturePreset("player", *engine::objectLibrary.getRarity("rarity_common"));
	playerCreature->glyph.character = '@';
	playerCreature->glyph.fgColor = TCODColor::lightAmber;
	playerHandler.setPlayerCreature(playerCreature);

	//Quest
	std::shared_ptr<Quest> questDebug = std::shared_ptr<Quest>(new QuestTheGoblinKing());
	questHandler.setCurrentQuest(questDebug);
	questHandler.travelToVillage();

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