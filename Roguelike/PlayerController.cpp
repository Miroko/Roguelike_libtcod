#include "PlayerController.h"
#include "Engine.h"
#include "KeyMapping.h"
#include "Door.h"

bool PlayerController::handleKey(TCOD_key_t key){
	switch (key.c) {
		case UNDEFINED : return move(key);
		case KEY_ATTACK: return attack();
		case KEY_TAKE: return take();
		case KEY_OPERATE: return operate();
		case KEY_TALK: return talk();
		case KEY_LEAVE_AREA: Engine::questHandler.toVillage(); return false;
		default:{
			if (!Engine::GUI.log.isOpen) Engine::GUI.log.open();
			Engine::GUI.log.addMessage("Invalid input, press 'h' for help."); return false;
		}
	}
}

bool PlayerController::move(TCOD_key_t key){
	Point2D direction = KeyMapping::direction(key.vk);

	if (direction.undefined()) return false;
	else if (direction == CENTER) return true; //==Wait
	else return Engine::area.moveDynamicObject(*playerCreature, playerCreature->location + direction);
}

bool PlayerController::attack(){	
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false); // Wait for attack direction

	Point2D direction = KeyMapping::direction(key.vk);

	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<std::shared_ptr<DynamicObject>> objectsToAttack;
		objectsToAttack = Engine::area.getDynamicObjectsAt(playerCreature->location + direction);
		if (objectsToAttack.empty()) return false;
		else playerCreature->damage(*objectsToAttack.front()); return true; //Attack first at location
	}
}

bool PlayerController::take(){
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

bool PlayerController::operate(){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false);

	Point2D direction = KeyMapping::direction(key.vk);

	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;
		dynamicObjects = Engine::area.getDynamicObjectsAt(playerCreature->location + direction);
		if (dynamicObjects.empty()) return false;
		else if(dynamicObjects.size() == 1){ //No other dynamic objects blocking
			OperatableObject *operatableObject = dynamic_cast<OperatableObject*>(dynamicObjects.at(0).get());
			if (operatableObject != nullptr){
				if (operatableObject->isOn){
					operatableObject->off();
				}
				else{
					operatableObject->on();
				}
				return true;
			}
		}
	}
	return false;
}

bool PlayerController::talk(){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false);

	Point2D direction = KeyMapping::direction(key.vk);

	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;
		dynamicObjects = Engine::area.getDynamicObjectsAt(playerCreature->location + direction);
		if (dynamicObjects.empty()) return false;
		else{
			if (dynamicObjects.front() == nullptr) return false;
			else{
				Engine::GUI.dialog.setDialog(Engine::questHandler.currentQuest->getDialog(dynamicObjects.front()));
				Engine::GUI.dialog.open();
			}
		}
	}
	return false;
}