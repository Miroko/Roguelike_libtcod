#include "Engine.h"
#include "iostream"

Camera Engine::camera = Camera();
Inventory Engine::inventory = Inventory();
Log Engine::log = Log();
PlayerHandler Engine::playerHandler = PlayerHandler();
QuestHandler Engine::questHandler = QuestHandler();
Area Engine::area = Area();

void Engine::start(){

	// Init
	TCODConsole::initRoot(120, 60, "Roguelike", false);
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(100, 10);

	inventory.init();
	log.init();

	// Player
	Engine::playerHandler.playerObject = std::shared_ptr<AliveObject>(new Human("Player"));

	// Quest
	questHandler.addQuest(new ClearCave());
	questHandler.setCurrentQuest(questHandler.quests[0].get());
	questHandler.generateNextPhase();

	// Main loop
	while (!TCODConsole::isWindowClosed())
	{
		render();
		update(TCODConsole::checkForKeypress(TCOD_KEY_PRESSED), TCODSystem::getLastFrameLength());
	}
}

void Engine::update(TCOD_key_t key, float elapsed){
	if (playerHandler.handleKey(key)){
		// Require simulation update
		playerHandler.playerObject->calculateFov();

		for (auto &o : area.dynamicObjects){
			o->update();
		}

		camera.centerOn(playerHandler.playerObject->location);
	}
	// Realtime update
}

void Engine::render(){
	TCODConsole::root->clear();
	
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){		
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (area.bounds.contains(Point2D(x, y))){
				if (playerHandler.playerObject->inFov(x,y)){
					area.staticObjects[x][y]->render(x - camera.location.x, y - camera.location.y);
				}
			}
		}
	}

	for (auto &dynamicObject : area.dynamicObjects){
		int renderX = dynamicObject->location.x - camera.location.x;
		int renderY = dynamicObject->location.y - camera.location.y;
		dynamicObject->render(renderX, renderY);
	}

	if (inventory.isOpen){
		inventory.render();
	}
	
	//log.render();

	TCODConsole::root->flush();
}