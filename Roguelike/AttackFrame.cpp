#include "AttackFrame.h"
#include "KeyMapping.h"
#include "Engine.h"
#include "Direction.h"
#include "Weapon.h"
#include "Engine.h"

bool AttackFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == LEFT){
				if (selectedObjectIndex == 0) selectedObjectIndex = attackableObjects.size() - 1;
				else selectedObjectIndex--;
				updateTarget();
				handled = true;
			}
			else if (direction == RIGHT){
				if (selectedObjectIndex == attackableObjects.size() - 1) selectedObjectIndex = 0;
				else selectedObjectIndex++;
				updateTarget();
				handled = true;
			}
			else if (direction == CENTER){
				engine::playerHandler.getPlayerCreature()->attack(*attackableObjects.at(selectedObjectIndex));
				previouslyAttacked = attackableObjects.at(selectedObjectIndex);
				engine::requestUpdate = true;
				handled = true;
			}
		}
		if (!handled){
			handled = true;
			close();
		}
	}
	return handled;
}

//Get objects to attack and set target
void AttackFrame::update(){
	updateAttackableObjects();
	if (!attackableObjects.empty()){
		//try to keep same target
		int index = -1;
		bool indexSelected = false;
		for (auto &o : attackableObjects){
			++index;
			if (o == previouslyAttacked){
				selectedObjectIndex = index;
				indexSelected = true;
				break;
			}
		}
		if (!indexSelected) selectedObjectIndex = 0;
		updateTarget();
	}
	else{
		close();
	}
}

void AttackFrame::render(){
	GuiFrame::render();
	guiGameObjectDisplay.renderTo(*this, guiGameObjectDisplayBounds);
	//cursor
	TCODConsole::root->setCharBackground(
		attackableObjects.at(selectedObjectIndex)->location.x - engine::camera.location.x,
		attackableObjects.at(selectedObjectIndex)->location.y - engine::camera.location.y,
		Gui::INSPECTION_CURSOR,
		TCOD_BKGND_ALPHA(Gui::INSPECTION_CURSOR_ALPHA));
	blit();
}

void AttackFrame::updateTarget(){
	if (!attackableObjects.empty()){
		guiGameObjectDisplay.setDisplayedObject(attackableObjects.at(selectedObjectIndex).get());
	}
}

void AttackFrame::updateAttackableObjects(){
	attackableObjects.clear();
	Weapon *weapon = engine::playerHandler.getPlayerCreature()->inventory.getWeapons().at(0);
	//attack range
	Rectangle range = Rectangle(
		engine::playerHandler.getPlayerCreature()->location,
		engine::playerHandler.getPlayerCreature()->location)
		.expand(weapon->range);
	//get attackable creatures
	for (auto &creature : engine::areaHandler.getCurrentArea()->getCreatures(range)){
		attackableObjects.push_back(*creature);
	}
	//and operatables
	for (auto &creature : engine::areaHandler.getCurrentArea()->getOperatables(range)){
		attackableObjects.push_back(*creature);
	}
	//remove player and objects not in fov
	auto &o = attackableObjects.begin();
	while (o != attackableObjects.end()){
		if (o->get() == engine::playerHandler.getPlayerCreature().get() ||
			!engine::playerHandler.getPlayerCreature()->ai->inFov(o->get()->location)){
			o = attackableObjects.erase(o);
		}
		else ++o;
	}
}

void AttackFrame::onOpen(){
	auto &weapons = engine::playerHandler.getPlayerCreature()->inventory.getWeapons();
	if (!weapons.empty()){
		update();
		if (attackableObjects.empty()){
			if (weapons.at(0)->type == GameObject::WEAPON_MELEE){
				engine::gui.log.addMessage("Nothing to attack.");
			}
			else if (weapons.at(0)->type == GameObject::WEAPON_RANGED){
				engine::gui.log.addMessage("Nothing to shoot at.");
			}
		}
	}
	else {
		engine::gui.log.addMessage("I need to equip a weapon first.");
		close();
	}
}

void AttackFrame::init(Rectangle &bounds){
	GuiFrame::init(bounds);
	guiGameObjectDisplayBounds = Rectangle(getWidth(), getHeight());
}
