#include "Engine.h"
#include "Weapon.h"
#include "ObjectLibrary.h"

Gui Engine::GUI = Gui();
Camera Engine::camera = Camera();
PlayerController Engine::playerController = PlayerController();
QuestHandler Engine::questHandler = QuestHandler();
Area Engine::area = Area();
VisualEffectHandler Engine::visualEffectHandler = VisualEffectHandler();

void Engine::start(){
	TCODSystem::setFps(10);
	TCODConsole::setKeyboardRepeat(20, 20);

	GUI.init();

	// Player creation
	playerController.playerCreature = ObjectLibrary::generateCreature(
		ObjectLibrary::MAN,
		RarityType::COMMON,
		ObjectLibrary::MAN_EQUIPMENT,
		ObjectLibrary::MAN_LOOT);
	playerController.playerCreature->name = "Player";
	playerController.playerCreature->glyph.character = '@';
	playerController.playerCreature->glyph.fgColor = TCODColor::lightestBlue;

	//Inventory
	std::shared_ptr<Item> sword = ObjectLibrary::generateWeapon(ObjectLibrary::SWORD, RarityType::COMMON);
	std::shared_ptr<Item> bow = ObjectLibrary::generateWeapon(ObjectLibrary::BOW, RarityType::UNCOMMON);
	std::shared_ptr<Item> armorHead = ObjectLibrary::generateArmor(ObjectLibrary::LEATHER_HEAD, RarityType::RARE);
	std::shared_ptr<Item> armorBody = ObjectLibrary::generateArmor(ObjectLibrary::LEATHER_BODY, RarityType::EPIC);
	std::shared_ptr<Item> armorHand = ObjectLibrary::generateArmor(ObjectLibrary::LEATHER_HAND, RarityType::UNIQUE);
	std::shared_ptr<Item> armorLeg = ObjectLibrary::generateArmor(ObjectLibrary::LEATHER_LEG, RarityType::RARE);
	std::shared_ptr<Item> healthPotion = ObjectLibrary::generateConsumable(ObjectLibrary::HEALTH_POTION);
	GUI.inventory.addItem(healthPotion);
	GUI.inventory.addItem(sword);
	GUI.inventory.addItem(bow);
	GUI.inventory.addItem(armorBody);
	GUI.inventory.equip(sword);
	GUI.inventory.equip(armorHead);
	GUI.inventory.equip(armorBody);
	GUI.inventory.equip(armorHand);
	GUI.inventory.equip(armorLeg);
	GUI.inventory.equip(bow);
	
	// Quest
	questHandler.setCurrentQuest(std::shared_ptr<Quest>(new TheGoblinKing()));
	questHandler.toVillage();

	// Main loop
	while (!TCODConsole::isWindowClosed())
	{
		TCODConsole::root->clear();

		if (handleInput(TCODConsole::checkForKeypress(TCOD_KEY_PRESSED))){
			updateSimulation();
			questHandler.update();
		}

		renderRealTime(TCODSystem::getLastFrameLength());
		
		TCODConsole::root->flush();
	}
}

//True if input action requires simulation update
bool Engine::handleInput(TCOD_key_t key){
	bool requireUpdate = false;
	if (key.vk != TCODK_NONE){
		//Input handled in gui
		if (GUI.handleKey(key, requireUpdate)) return requireUpdate;

		//Handle input in player controls
		bool playerControls = playerController.handleKey(key);
		if (!requireUpdate) requireUpdate = playerControls;
	}
	return requireUpdate;
}

void Engine::updateSimulation(){
	area.update();
	area.cleanDeadDynamicObjects();

	if (playerController.playerCreature->isDead){
		//Respawn in village, reset quest
		questHandler.setCurrentQuest(std::shared_ptr<Quest>(new TheGoblinKing()));
		playerController.playerCreature->health = playerController.playerCreature->healthMax;
		playerController.playerCreature->isDead = false;
		questHandler.toVillage();
	}

	camera.centerOn(playerController.playerCreature->location);
}

void Engine::renderRealTime(float elapsed){
	renderSimulation();
	visualEffectHandler.render();
	GUI.render();
}

void Engine::renderSimulation(){	
	//Render static objects in fov
	for (int x = camera.location.x; x < camera.location.x + camera.getWidth(); x++){		
		for (int y = camera.location.y; y < camera.location.y + camera.getHeight(); y++){
			if (area.bounds.inside(Point2D(x, y))){
				if (playerController.playerCreature->ai.inFov(x,y)){
					area.staticObjects[x][y]->render(x - camera.location.x, y - camera.location.y);
				}
			}
		}
	}

	//Render items in fov
	for (auto &item : area.items){
		int renderX = item->location.x - camera.location.x;
		int renderY = item->location.y - camera.location.y;
		if (playerController.playerCreature->ai.inFov(item->location.x, item->location.y)){
			item->render(renderX, renderY);
		}
	}

	//Render portals in fov
	for (auto &portal : area.portals){
		int renderX = portal->location.x - camera.location.x;
		int renderY = portal->location.y - camera.location.y;
		if (playerController.playerCreature->ai.inFov(portal->location.x, portal->location.y)){
			portal->render(renderX, renderY);
		}
	}

	//Render operatable objects in fov
	for (auto &operatable : area.operatableObjects){
		int renderX = operatable->location.x - camera.location.x;
		int renderY = operatable->location.y - camera.location.y;
		if (playerController.playerCreature->ai.inFov(operatable->location.x, operatable->location.y)){
			operatable->render(renderX, renderY);
		}
	}

	//Render creatures objects in fov
	for (auto &creature : area.creatures){
		int renderX = creature->location.x - camera.location.x;
		int renderY = creature->location.y - camera.location.y;
		if (playerController.playerCreature->ai.inFov(creature->location.x, creature->location.y)){
			creature->render(renderX, renderY);
		}
	}
}