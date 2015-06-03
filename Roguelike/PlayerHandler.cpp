#include "PlayerHandler.h"
#include "Engine.h"

void PlayerHandler::addItem(std::shared_ptr<Item> item){
	items.push_back(item);
}

bool PlayerHandler::handleKey(TCOD_key_t key){
	bool requireUpdate = false;

	bool moved = move(key.vk);
	if (!requireUpdate) requireUpdate = moved;

	leaveArea(key.c);
	inventory(key.c);

	return requireUpdate;
}

bool PlayerHandler::move(TCOD_keycode_t code){
	switch (code)
	{
	case TCODK_KP4:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x - 1, playerObject->location.y));
		return true;
		break;
	case TCODK_KP8:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x, playerObject->location.y - 1));
		return true;
		break;
	case TCODK_KP6:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x + 1, playerObject->location.y));
		return true;
		break;
	case TCODK_KP2:
		Engine::area.moveDynamicObject(playerObject.get(), Point2D(playerObject->location.x, playerObject->location.y + 1));
		return true;
		break;
	default:
		break;
	}
	return false;
}

void PlayerHandler::leaveArea(char keyChar){
	if (keyChar == 'l'){
		Engine::questHandler.generateNextPhase();
	}
}

void PlayerHandler::inventory(char keyChar){
	if (keyChar == 'i'){
		Engine::inventory.openOrClose();
	}
}