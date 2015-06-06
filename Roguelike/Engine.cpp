#include "Engine.h"
#include "Human.h"

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
	inventory.init(false);
	log.init(true);

	// Player
	playerHandler.playerCreature = std::shared_ptr<AliveObject>(new Race::Human::HumanBase(Race::Human::MAN_BASE));
	playerHandler.playerCreature->name = "Player";
	playerHandler.playerCreature->glyph.character = '@';
	playerHandler.playerCreature->glyph.fgColor = TCODColor::lightestBlue;
	//Inventory
	inventory.weapons.add(std::shared_ptr<Weapon>(new Sword()));
	inventory.equip(*inventory.weapons.items.back().get());

	// Quest
	questHandler.addQuest(new ClearCave());
	questHandler.setCurrentQuest(questHandler.quests[0].get());
	questHandler.generateNextPhase();

	// Main loop
	while (!TCODConsole::isWindowClosed())
	{
		if (handleInput(TCODConsole::checkForKeypress(TCOD_KEY_PRESSED))){
			updateSimulation();
		}
		updateGraphics(TCODSystem::getLastFrameLength());
	}
}

//True if input action requires simulation update
bool Engine::handleInput(TCOD_key_t key){
	bool requireUpdate = false;
	
	bool playerControls = playerHandler.handleKey(key);
	if (!requireUpdate) requireUpdate = playerControls;

	if (inventory.isOpen){
		bool inventoryConrols = inventory.handleKey(key);
		if (!requireUpdate) requireUpdate = inventoryConrols;
	}

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

void Engine::updateGraphics(float elapsed){
	// Realtime update
	// Effects etc. here
	render();
}

void Engine::render(){
	TCODConsole::root->clear();
	
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

	if (log.isOpen){
		log.render();
	}

	if (inventory.isOpen){
		inventory.render();
	}

	TCODConsole::root->flush();
}