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
	playerHandler.playerObject = std::shared_ptr<AliveObject>(new Human("Player"));
	playerHandler.playerObject->weapon = &playerHandler.playerObject->loot->weapons[0];

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
		//Player action requires simulation update
		//Update
		for (auto &o : area.dynamicObjects){
			if (!o->isDead){ //Object can be set to null for removal
				o->update();
			}
		}
		//Clean objects set to null
		area.cleanDeadObjects();
		//Is player dead
		if (playerHandler.playerObject->isDead){
			//Respawn in new area
			playerHandler.playerObject->health = 100;
			playerHandler.playerObject->isDead = false;
			questHandler.generateNextPhase();			
		}
		//Center camera
		camera.centerOn(playerHandler.playerObject->location);
	}
	// Realtime update
	// Effects etc. here
}

void Engine::render(){
	TCODConsole::root->clear();
	
	//Render static objects in fov
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){		
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (area.bounds.contains(Point2D(x, y))){
				if (playerHandler.playerObject->inFov(x,y)){
					area.staticObjects[x][y]->render(x - camera.location.x, y - camera.location.y);
				}
			}
		}
	}
	//Render dynamic objects in fov
	for (auto &dynamicObject : area.dynamicObjects){
		int renderX = dynamicObject->location.x - camera.location.x;
		int renderY = dynamicObject->location.y - camera.location.y;
		if (playerHandler.playerObject->inFov(dynamicObject->location.x, dynamicObject->location.y)){
			dynamicObject->render(renderX, renderY);
		}
	}

	if (log.isOpen){
		log.render();
	}

	if (inventory.isOpen){
		inventory.render();
	}

	TCODConsole::root->flush();
}