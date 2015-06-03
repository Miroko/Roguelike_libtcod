#include "PlayerHandler.h"
#include "Engine.h"
#include <iostream>

void PlayerHandler::addItem(std::shared_ptr<Item> item){
	items.push_back(item);
}

bool PlayerHandler::handleKey(TCOD_key_t key){
	bool requireUpdate = false;

	bool moved = move(key);
	if (!requireUpdate) requireUpdate = moved;

	bool attacked = attack(key);
	if (!requireUpdate) requireUpdate = attacked;

	leaveArea(key);
	inventory(key);

	return requireUpdate;
}

bool PlayerHandler::move(TCOD_key_t key){
	switch (key.vk)
	{
	case TCODK_KP4:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x - 1, playerObject->location.y));
		return true;
	case TCODK_KP7:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x - 1, playerObject->location.y - 1));
		return true;
	case TCODK_KP8:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x, playerObject->location.y - 1));
		return true;
	case TCODK_KP9:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x + 1, playerObject->location.y - 1));
		return true;
	case TCODK_KP6:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x + 1, playerObject->location.y));
		return true;
	case TCODK_KP3:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x + 1, playerObject->location.y + 1));
		return true;
	case TCODK_KP2:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x, playerObject->location.y + 1));
		return true;
	case TCODK_KP1:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x - 1, playerObject->location.y + 1));
		return true;
	default:
		break;
	}
	return false;
}

bool PlayerHandler::attack(TCOD_key_t key){
	if (key.c == 'a'){
		while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){} // Wait for key release
		TCOD_key_t key = TCODConsole::waitForKeypress(true); // Get attack direction
		std::vector<DynamicObject*> objectsToAttack;
		switch (key.vk)
		{
		case TCODK_KP4:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x - 1, playerObject->location.y));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP7:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x - 1, playerObject->location.y - 1));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP8:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x, playerObject->location.y - 1));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP9:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x + 1, playerObject->location.y - 1));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP6:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x + 1, playerObject->location.y));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP3:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x + 1, playerObject->location.y + 1));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP2:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x, playerObject->location.y + 1));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		case TCODK_KP1:
			objectsToAttack = Engine::area.getDynamicObjectsAt(Point2D(playerObject->location.x - 1, playerObject->location.y + 1));
			if (!objectsToAttack.empty()){ playerObject->attack(*objectsToAttack[0]); return true; }
			break;
		default:
			break;
		}
	}
	return false;
}

void PlayerHandler::leaveArea(TCOD_key_t key){
	if (key.c == 'l'){
		Engine::questHandler.generateNextPhase();
	}
}

void PlayerHandler::inventory(TCOD_key_t key){
	if (key.c == 'i'){
		Engine::inventory.openOrClose();
	}
}