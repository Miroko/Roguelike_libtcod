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
	case KEY_DEBUG: engine::renderWithoutFov = !engine::renderWithoutFov; return false;
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
	engine::gui.attack.open();
	return false;
}
bool PlayerController::take(){
	std::vector<std::shared_ptr<Item>> &itemsToTake = engine::areaHandler.getCurrentArea()->getItems(engine::playerHandler.getPlayerCreature()->location);
	if(!itemsToTake.empty()){
		while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
		for (auto &item : itemsToTake){
			engine::gui.pickFrame.pickableItems.add(item);
		}
		engine::gui.pickFrame.open();
	}
	return false;
}
bool PlayerController::operate(){
	while (TCODConsole::checkForKeypress(TCOD_KEY_RELEASED).vk == TCODK_NONE){};
	TCOD_key_t key = TCODConsole::waitForKeypress(false);
	Point2D direction = KeyMapping::direction(key.vk);
	if (direction.undefined()) return false;
	else if (direction == CENTER) return false;
	else{
		auto &operatable = engine::areaHandler.getCurrentArea()->getOperatable(engine::playerHandler.getPlayerCreature()->location + direction);
		if (&operatable){
			operatable.operate(*engine::playerHandler.getPlayerCreature());
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
		Point2D talkDirection = engine::playerHandler.getPlayerCreature()->location + direction;
		auto &creature = engine::areaHandler.getCurrentArea()->getCreature(talkDirection);
		if (&creature){
			engine::gui.dialog.setDialog(engine::questHandler.getCurrentQuest()->getCurrentPhase()->getDialog(creature));
			engine::gui.dialog.open();
		}
	}
	return false;
}
bool PlayerController::enterArea(){
	if (engine::areaHandler.getCurrentArea()->getTile(engine::playerHandler.getPlayerCreature()->location)->type == Item::PORTAL ||
		engine::questHandler.getCurrentQuest()->getCurrentPhase() == engine::questHandler.getCurrentQuest()->getVillage()){
		engine::questHandler.travelToNextPhase();
	}
	return false;
}
bool PlayerController::leaveArea(){
	if (engine::areaHandler.getCurrentArea()->getTile(engine::playerHandler.getPlayerCreature()->location)->type == Item::PORTAL){
		engine::questHandler.travelToVillage();
	}
	return false;
}