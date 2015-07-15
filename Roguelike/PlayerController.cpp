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
	case KEY_ATTACK: return attack();
	case KEY_TAKE: return take();
	case KEY_OPERATE: return operate();
	case KEY_TALK: return talk();
	case KEY_ENTER_AREA: return enterArea();
	case KEY_LEAVE_AREA: return leaveArea();
	case KEY_DEBUG: engine::areaHandler.getCurrentArea()->SEE_THROUGH = !engine::areaHandler.getCurrentArea()->SEE_THROUGH; return false;
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
bool PlayerController::attack(){
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
	std::vector<std::shared_ptr<Item>*> itemsToTake = engine::areaHandler.getCurrentArea()->getItemsAt(engine::playerHandler.getPlayerCreature()->location);
	if (itemsToTake.empty()) return false;
	else{
		while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
		for (auto &item : itemsToTake){
			engine::playerHandler.playerInventory.temporary.add(*item);
		}
		engine::gui.pickFrame.setItemContainer(engine::playerHandler.playerInventory.temporary);
		engine::gui.pickFrame.open();
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
bool PlayerController::talk(){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false);
	Point2D direction = KeyMapping::direction(key.vk);
	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		std::vector<Creature*> creatures;
		Point2D talkDirection = engine::playerHandler.getPlayerCreature()->location + direction;
		for (auto &creature : engine::areaHandler.getCurrentArea()->getCreatures(talkDirection)){
			creatures.push_back(creature->get());
		}
		if (creatures.empty()) return false;
		else{
			engine::gui.dialog.setDialog(engine::questHandler.getCurrentQuest()->getCurrentPhase()->getDialog(*creatures.front()));
			engine::gui.dialog.open();
		}
	}
	return false;
}
bool PlayerController::enterArea(){
	if (engine::areaHandler.getCurrentArea()->getTile(engine::playerHandler.getPlayerCreature()->location)->type == Item::PORTAL ||
		engine::questHandler.getCurrentQuest()->getCurrentPhase() == engine::questHandler.getCurrentQuest()->getVillage()){
		engine::questHandler.travelToNextPhase();
		return true;
	}
	return false;
}
bool PlayerController::leaveArea(){
	if (engine::areaHandler.getCurrentArea()->getTile(engine::playerHandler.getPlayerCreature()->location)->type == Item::PORTAL){
		engine::questHandler.travelToVillage();
		return true;
	}
	return false;
}