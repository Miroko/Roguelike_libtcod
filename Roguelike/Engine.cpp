#include "Engine.h"
#include "human.h"

Gui Engine::GUI = Gui();
Camera Engine::camera = Camera();
PlayerHandler Engine::playerHandler = PlayerHandler();
QuestHandler Engine::questHandler = QuestHandler();
Area Engine::area = Area();

void Engine::start(){
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(100, 10);

	GUI.log.resize(Rectangle(Point2D(0, TCODConsole::root->getHeight() - 12), Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));
	GUI.inventory.resize(Rectangle(Point2D(TCODConsole::root->getWidth() - 30, 0), Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));

	// Player
	playerHandler.playerCreature = std::shared_ptr<AliveObject>(new race::human::HumanBase(race::human::MAN_BASE));
	playerHandler.playerCreature->name = "Player";
	playerHandler.playerCreature->glyph.character = '@';
	playerHandler.playerCreature->glyph.fgColor = TCODColor::lightestBlue;
	//Inventory
	GUI.inventory.weapons.add(std::shared_ptr<Weapon>(new Sword()));
	GUI.inventory.equip(*GUI.inventory.weapons.items.back().get());

	// Quest
	questHandler.addQuest(new ClearCave());
	questHandler.setCurrentQuest(questHandler.quests[0].get());
	questHandler.generateNextPhase();

	// Main loop
	while (!TCODConsole::isWindowClosed())
	{
		TCODConsole::root->clear();

		if (handleInput(TCODConsole::checkForKeypress(TCOD_KEY_PRESSED))){
			updateSimulation();
		}
		renderSimulation();
		renderRealTime(TCODSystem::getLastFrameLength());
		
		TCODConsole::root->flush();
	}
}

//True if input action requires simulation update
bool Engine::handleInput(TCOD_key_t key){
	bool requireUpdate = false;
	
	if (GUI.inventory.open){
		bool inventoryAction = GUI.inventory.handleKey(key);
		if (!requireUpdate) requireUpdate = inventoryAction;
	}

	if (GUI.log.open){
		bool logAction = GUI.log.handleKey(key);
		if (!requireUpdate) requireUpdate = logAction;
	}

	bool playerControls = playerHandler.handleKey(key);
	if (!requireUpdate) requireUpdate = playerControls;

	return requireUpdate;
}

void Engine::updateSimulation(){
	for (auto &o : area.dynamicObjects){
		if (!o->isDead){
			o->update();
		}
	}

	area.cleanDeadObjects();

	if (playerHandler.playerCreature->isDead){
		//Respawn in new area
		playerHandler.playerCreature->health = 100;
		playerHandler.playerCreature->isDead = false;
		questHandler.generateNextPhase();
	}
	camera.centerOn(playerHandler.playerCreature->location);
}

void Engine::renderRealTime(float elapsed){
	if (GUI.log.open) GUI.log.render(elapsed);
	if (GUI.inventory.open)	GUI.inventory.render(elapsed);
}

void Engine::renderSimulation(){	
	//Render static objects in fov
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){		
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (area.bounds.contains(Point2D(x, y))){
				if (playerHandler.playerCreature->inFov(x,y)){
					area.staticObjects[x][y]->render(x - camera.location.x, y - camera.location.y);
				}
			}
		}
	}
	//Render items in fov
	for (auto &item : area.items){
		int renderX = item->location.x - camera.location.x;
		int renderY = item->location.y - camera.location.y;
		if (playerHandler.playerCreature->inFov(item->location.x, item->location.y)){
			item->render(renderX, renderY);
		}
	}

	//Render dynamic objects in fov
	for (auto &dynamicObject : area.dynamicObjects){
		int renderX = dynamicObject->location.x - camera.location.x;
		int renderY = dynamicObject->location.y - camera.location.y;
		if (playerHandler.playerCreature->inFov(dynamicObject->location.x, dynamicObject->location.y)){
			dynamicObject->render(renderX, renderY);
		}
	}
}