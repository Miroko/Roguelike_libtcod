#include "PlayerHandler.h"
#include "Engine.h"

bool PlayerHandler::handleKey(TCOD_key_t key){
	switch (key.c) {
		case 0 : return move(key);
		case 'a': return attack();
		case 't': return take();
		case 'i': Engine::GUI.inventory.openClose(); return false;
		case 'l': Engine::questHandler.generateNextPhase(); return false;
		case 'e': Engine::GUI.equipment.openClose(); return false;
		case 'q': Engine::GUI.quest.openClose(); return false;
		case 'h': Engine::GUI.help.openClose(); return false;
		case 'L': Engine::GUI.log.openClose(); return false;
		default:{
			if (!Engine::GUI.log.open) Engine::GUI.log.openClose();
			Engine::GUI.log.addMessage("Invalid input, press 'h' for help."); return false;
		}
	}
}

bool PlayerHandler::move(TCOD_key_t key){
	Point2D direction;
	switch (key.vk) {
		case TCODK_KP1: direction = DOWN_LEFT; break;
		case TCODK_KP4: direction = LEFT; break;
		case TCODK_KP7: direction = UP_LEFT; break;
		case TCODK_KP8: direction = UP; break;
		case TCODK_KP9: direction = UP_RIGHT; break;
		case TCODK_KP6: direction = RIGHT; break;
		case TCODK_KP3: direction = DOWN_RIGHT; break;
		case TCODK_KP2: direction = DOWN; break;
		case TCODK_KP5: direction = CENTER; break; //==Wait
		default: break;
	}

	if (direction.undefined()) return false;
	else if (direction == CENTER) return true;
	else return Engine::area.moveDynamicObject(*playerCreature, playerCreature->location + direction);
}

bool PlayerHandler::attack(){	
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false); // Wait for attack direction

	Point2D direction;
	switch (key.vk) {
		case TCODK_KP1: direction = DOWN_LEFT; break;
		case TCODK_KP4: direction = LEFT; break;
		case TCODK_KP7: direction = UP_LEFT; break;
		case TCODK_KP8: direction = UP; break;
		case TCODK_KP9: direction = UP_RIGHT; break;
		case TCODK_KP6: direction = RIGHT; break;
		case TCODK_KP3: direction = DOWN_RIGHT; break;
		case TCODK_KP2: direction = DOWN; break;
		case TCODK_KP5: direction = CENTER; break;
		default: break;
	}

	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<DynamicObject*> objectsToAttack;
		objectsToAttack = Engine::area.getDynamicObjectsAt(playerCreature->location + direction);
		if (objectsToAttack.empty()) return false;
		else playerCreature->attack(*objectsToAttack.front()); return true; //Attack first at location
	}
}

bool PlayerHandler::take(){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	std::vector<std::shared_ptr<Item>> itemsToTake;
	itemsToTake = Engine::area.getItemsAt(playerCreature->location);
	if (itemsToTake.empty()) return false;
	else{
		Engine::GUI.pickFrame.items.items.clear();
		Engine::GUI.pickFrame.openClose();
		for (auto &item : itemsToTake){
			Engine::GUI.pickFrame.items.add(item);
		}
		return true;
	}
}