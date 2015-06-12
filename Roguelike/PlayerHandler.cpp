#include "PlayerHandler.h"
#include "Engine.h"
#include "KeyMapping.h"

bool PlayerHandler::handleKey(TCOD_key_t key){
	switch (key.c) {
		case UNDEFINED : return move(key);
		case KEY_ATTACK: return attack();
		case KEY_TAKE: return take();
		case KEY_LEAVE_AREA: Engine::questHandler.generateNextPhase(); return false;
		default:{
			if (!Engine::GUI.log.isOpen) Engine::GUI.log.open();
			Engine::GUI.log.addMessage("Invalid input, press 'h' for help."); return false;
		}
	}
}

bool PlayerHandler::move(TCOD_key_t key){
	Point2D direction = KeyMapping::direction(key.vk);

	if (direction.undefined()) return false;
	else if (direction == CENTER) return true; //==Wait
	else return Engine::area.moveDynamicObject(*playerCreature, playerCreature->location + direction);
}

bool PlayerHandler::attack(){	
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false); // Wait for attack direction

	Point2D direction = KeyMapping::direction(key.vk);

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
		for (auto &item : itemsToTake){
			Engine::GUI.pickFrame.addItem(item);
		}
		Engine::GUI.pickFrame.open();
		return true;
	}
}