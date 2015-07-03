#include "PlayerController.h"
#include "Engine.h"
#include "KeyMapping.h"
#include "Direction.h"
#include "Door.h"
#include "Quest.h"
#include "Weapon.h"

bool PlayerController::handleKey(TCOD_key_t key){
	Point2D direction = KeyMapping::direction(key.vk);
	switch (key.c) {
	case KEY_UNDEFINED: return move(direction);
	case KEY_ATTACK: return attack(direction);
	case KEY_TAKE: return take();
	case KEY_OPERATE: return operate(direction);
	case KEY_TALK: return talk(direction);
	case KEY_LEAVE_Area: return leaveArea();
	default:
		if (!engine::gui.log.isOpen) engine::gui.log.open();
		engine::gui.log.addMessage("Invalid input, press 'h' for help.");
		return false;
	}
}

bool PlayerController::move(Point2D &direction){
	if (direction.undefined()) return false;
	else if (direction == CENTER) return wait();
	else return engine::playerHandler.getPlayerCreature()->move(engine::playerHandler.getPlayerCreature()->location + direction);
}
bool PlayerController::wait(){
	take();
	return true;
}
bool PlayerController::attack(Point2D &direction){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	if (engine::playerHandler.getPlayerCreature()->inventory.currentWeapon != nullptr){
		switch (engine::playerHandler.getPlayerCreature()->inventory.currentWeapon->type){
		case Weapon::WEAPON_MELEE:{
			TCOD_key_t key = TCODConsole::waitForKeypress(false); // Wait for attack direction
			Point2D attackDirection = KeyMapping::direction(key.vk);
			if (attackDirection.undefined()) return false;
			else if (attackDirection == CENTER) return false;
			else{
				std::vector<std::shared_ptr<DynamicObject>> objectsToAttack;
				Point2D attackLocation = engine::playerHandler.getPlayerCreature()->location + attackDirection;
				for (auto &creature : engine::areaHandler.getCurrentArea()->getCreatures(attackLocation)){
					objectsToAttack.push_back(*creature);
				}
				if (objectsToAttack.empty()){
					//no creatures to attack
					//check for operatables
					for (auto &operatable : engine::areaHandler.getCurrentArea()->getOperatables(attackLocation)){
						objectsToAttack.push_back(*operatable);
					}
				}
				if (objectsToAttack.empty()) return false;
				else engine::playerHandler.getPlayerCreature()->attack(*objectsToAttack.front()); return true; //Attack first at location
			}
		}break;
		case Weapon::WEAPON_RANGED:{
			Rectangle range = Rectangle(engine::playerHandler.getPlayerCreature()->location, engine::playerHandler.getPlayerCreature()->location);
			range.expand(8);
			std::vector<std::shared_ptr<DynamicObject>> objectsInRange;
			//can target creatures
			for (auto &creature : engine::areaHandler.getCurrentArea()->getCreatures(range)){
				objectsInRange.push_back(*creature);
			}
			//and operatables
			for (auto &operatable : engine::areaHandler.getCurrentArea()->getOperatables(range)){
				objectsInRange.push_back(*operatable);
			}
			auto &o = objectsInRange.begin();
			while (o != objectsInRange.end()){
				if (o->get() == engine::playerHandler.getPlayerCreature().get() ||
					!engine::playerHandler.getPlayerCreature()->ai->inFov(o->get()->location)){
					//Remove player and objects not in fov
					o = objectsInRange.erase(o);
				}
				else ++o;
			}
			if (objectsInRange.empty()) engine::gui.log.addMessage("Nothing to shoot at.");
			else {
				engine::gui.attack.setAttackableObjects(objectsInRange);
				engine::gui.attack.open();
			}
		}break;
		}
	}
	return false;
}
bool PlayerController::take(){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	std::vector<std::shared_ptr<Item>*> itemsToTake = engine::areaHandler.getCurrentArea()->getItemsAt(engine::playerHandler.getPlayerCreature()->location);
	if (itemsToTake.empty()) return false;
	else{
		for (auto &item : itemsToTake){
			engine::playerHandler.playerInventory.temporary.add(*item);
		}
		engine::gui.pickFrame.setItemContainer(engine::playerHandler.playerInventory.temporary);
		engine::gui.pickFrame.open();
		return true;
	}
}
bool PlayerController::operate(Point2D &direction){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false);
	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<std::shared_ptr<OperatableObject>*> operatables;
		operatables = engine::areaHandler.getCurrentArea()->getOperatables(engine::playerHandler.getPlayerCreature()->location + direction);
		if (operatables.empty()) return false;
		else{
			std::shared_ptr<OperatableObject> operatable = *operatables.front();
			if (operatable->isOn) operatable->off();
			else operatable->on();
			return true;
		}
	}
	return false;
}
bool PlayerController::talk(Point2D &direction){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false);
	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<std::shared_ptr<DynamicObject>> dynamicObjects;
		Point2D talkDirection = engine::playerHandler.getPlayerCreature()->location + direction;
		for (auto &creature : engine::areaHandler.getCurrentArea()->getCreatures(talkDirection)){
			dynamicObjects.push_back(*creature);
		}
		if (dynamicObjects.empty()) return false;
		else{
			engine::gui.dialog.setDialog(engine::questHandler.getCurrentQuest()->getCurrentPhase()->getDialog(*dynamicObjects.front()));
			engine::gui.dialog.open();
		}
	}
	return false;
}
bool PlayerController::leaveArea(){
	engine::questHandler.travelToVillage();
	return true;
}