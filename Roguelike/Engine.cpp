#include "Engine.h"
#include "Human.h"
#include "Weapon.h"

Gui Engine::GUI = Gui();
Camera Engine::camera = Camera();
PlayerController Engine::playerController = PlayerController();
QuestHandler Engine::questHandler = QuestHandler();
Area Engine::area = Area();

void Engine::start(){
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(100, 20);

	GUI.log.resize(Rectangle(Point2D(0, TCODConsole::root->getHeight() - 12), Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));
	GUI.inventory.resize(Rectangle(Point2D(TCODConsole::root->getWidth() - 30, 0), Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));
	GUI.equipment.resize(Rectangle(Point2D(TCODConsole::root->getWidth() - 30, 0), Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));
	GUI.quest.resize(Rectangle(Point2D(TCODConsole::root->getWidth()/2 - 30, 1), Point2D(TCODConsole::root->getWidth()/2 + 30, TCODConsole::root->getHeight()-1)));
	GUI.help.resize(Rectangle(Point2D(0, 0), Point2D(TCODConsole::root->getWidth(), TCODConsole::root->getHeight())));
	GUI.pickFrame.resize(Rectangle(Point2D(TCODConsole::root->getWidth() / 2 - 10, 10), Point2D(TCODConsole::root->getWidth() / 2 + 10, TCODConsole::root->getHeight() - 20)));
	GUI.statistics.resize(Rectangle(Point2D(TCODConsole::root->getWidth() - 30, 0), Point2D(TCODConsole::root->getWidth(), 30 )));
	GUI.inspection.resize(Rectangle(Point2D(0, 0), Point2D(30, 30)));

	// Player creation
	playerController.playerCreature = Creature::newCreature(MAN, false);
	playerController.playerCreature->name = "Player";
	playerController.playerCreature->glyph.character = '@';
	playerController.playerCreature->glyph.fgColor = TCODColor::lightestBlue;
	//Inventory
	std::shared_ptr<Item> sword = Item::newItem(SWORD);
	std::shared_ptr<Item> healthPotion = Item::newItem(HEALTH_POTION);
	GUI.inventory.addItem(healthPotion);
	GUI.inventory.addItem(sword);
	GUI.inventory.equip(sword);
	
	// Quest
	questHandler.addQuest(new TheGoblinKing());
	questHandler.setCurrentQuest(questHandler.quests[0].get());
	questHandler.toVillage();

	// Main loop
	while (!TCODConsole::isWindowClosed())
	{
		TCODConsole::root->clear();

		if (handleInput(TCODConsole::checkForKeypress(TCOD_KEY_PRESSED))){
			updateSimulation();
			questHandler.update();
		}
		renderSimulation();
		renderRealTime(TCODSystem::getLastFrameLength());
		
		TCODConsole::root->flush();
	}
}

//True if input action requires simulation update
bool Engine::handleInput(TCOD_key_t key){
	bool requireUpdate = false;
	if (key.vk != TCODK_NONE){
		//Input handled in gui
		if (GUI.handleKey(key)) return false;

		//Handle input in player controls
		bool playerControls = playerController.handleKey(key);
		if (!requireUpdate) requireUpdate = playerControls;
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

	if (playerController.playerCreature->isDead){
		//Respawn in village
		playerController.playerCreature->health = playerController.playerCreature->healthMax;
		playerController.playerCreature->isDead = false;
		questHandler.toVillage();
	}
	camera.centerOn(playerController.playerCreature->location);
}

void Engine::renderRealTime(float elapsed){
	GUI.render(elapsed);
}

void Engine::renderSimulation(){	
	//Render static objects in fov
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){		
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (area.bounds.inside(Point2D(x, y))){
				if (playerController.playerCreature->inFov(x,y)){
					area.staticObjects[x][y]->render(x - camera.location.x, y - camera.location.y);
				}
			}
		}
	}
	//Render items in fov
	for (auto &item : area.items){
		int renderX = item->location.x - camera.location.x;
		int renderY = item->location.y - camera.location.y;
		if (playerController.playerCreature->inFov(item->location.x, item->location.y)){
			item->render(renderX, renderY);
		}
	}

	//Render dynamic objects in fov
	for (auto &dynamicObject : area.dynamicObjects){
		int renderX = dynamicObject->location.x - camera.location.x;
		int renderY = dynamicObject->location.y - camera.location.y;
		if (playerController.playerCreature->inFov(dynamicObject->location.x, dynamicObject->location.y)){
			dynamicObject->render(renderX, renderY);
		}
	}
}