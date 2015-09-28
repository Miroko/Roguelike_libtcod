#include "ActionExecutionFrame.h"
#include "KeyMapping.h"
#include "Engine.h"
#include "Direction.h"
#include "Weapon.h"
#include "CreatureSkill.h"
#include "CreatureAction.h"
#include "DynamicObject.h"
#include "Engine.h"

void ActionExecutionFrame::executeSelectedAction(){
	for (auto &skill : engine::playerHandler.getPlayerCreature()->getCombatSkillsAndProficiencies()){
		if (skill.first == selectedSkill){
			for (auto &action : skill.first->getActionsAndProficiencies(skill.second)){
				if (action.first == selectedAction){
					engine::playerHandler.getPlayerCreature()->executeSkillAction(*skill.first, skill.second, *action.first, action.second,
						*attackableObjects.at(selectedObjectIndex));
					previousTarget = attackableObjects.at(selectedObjectIndex);
					engine::requestUpdate = true;
				}
			}
		}
	}
	//invalid action, skills or actions changed, weapon unequipped etc.
	open();
}

bool ActionExecutionFrame::validSelectedSkillAction(){
	for (auto &skill : engine::playerHandler.getPlayerCreature()->getCombatSkillsAndProficiencies()){
		if (skill.first == selectedSkill){
			for (auto &action : skill.first->getActionsAndProficiencies(skill.second)){
				if (action.first == selectedAction){
					return true;
				}
			}
		}
	}
	return false;
}

bool ActionExecutionFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == LEFT){
				if (selectedObjectIndex == 0) selectedObjectIndex = attackableObjects.size() - 1;
				else selectedObjectIndex--;
				handled = true;
			}
			else if (direction == RIGHT){
				if (selectedObjectIndex == attackableObjects.size() - 1) selectedObjectIndex = 0;
				else selectedObjectIndex++;
				handled = true;
			}
			else if (direction == CENTER){
				executeSelectedAction();
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
void ActionExecutionFrame::update(){
	updateAttackableObjects();
	if (!attackableObjects.empty()){
		//try to keep same target
		int index = -1;
		bool indexSelected = false;
		for (auto &o : attackableObjects){
			++index;
			if (o == previousTarget){
				selectedObjectIndex = index;
				indexSelected = true;
				break;
			}
		}
		if (!indexSelected) selectedObjectIndex = 0;
	}
	else{
		close();
	}
}

void ActionExecutionFrame::render(){
	GuiFrame::render();
	attackableObjects.at(selectedObjectIndex)->renderToFrame(*this, gameObjectDisplayBounds);
	//cursor
	TCODConsole::root->setCharBackground(
		attackableObjects.at(selectedObjectIndex)->location.x - engine::camera.location.x,
		attackableObjects.at(selectedObjectIndex)->location.y - engine::camera.location.y,
		Gui::INSPECTION_CURSOR,
		TCOD_BKGND_ALPHA(Gui::INSPECTION_CURSOR_ALPHA));
	blit();
}

void ActionExecutionFrame::updateAttackableObjects(){
	attackableObjects.clear();
	if (selectedAction->targetType == CreatureAction::SELF){
		attackableObjects.push_back(engine::playerHandler.getPlayerCreature().get());
	}
	else if (selectedAction->targetType == CreatureAction::IN_RANGE){
		Rectangle range = Rectangle(
			engine::playerHandler.getPlayerCreature()->location,
			engine::playerHandler.getPlayerCreature()->location)
			.expand(selectedAction->range);
		for (auto &creature : engine::areaHandler.getCurrentArea()->getCreatures(range)){
			attackableObjects.push_back(creature);
		}
		if (selectedSkill->isType(CreatureSkill::WEAPON)){
			for (auto &operatable : engine::areaHandler.getCurrentArea()->getOperatables(range)){
				attackableObjects.push_back(operatable);
			}
		}
		//remove player and objects not in fov
		auto &attackableObjectsIterator = attackableObjects.begin();
		while (attackableObjectsIterator != attackableObjects.end()){
			if (*attackableObjectsIterator == engine::playerHandler.getPlayerCreature().get() ||
				!engine::playerHandler.getPlayerCreature()->ai->inFov((*attackableObjectsIterator)->location)){
				attackableObjectsIterator = attackableObjects.erase(attackableObjectsIterator);
			}
			else ++attackableObjectsIterator;
		}
	}
}

void ActionExecutionFrame::onOpen(){
	if (!validSelectedSkillAction()){
		engine::gui.skill.open();
		close();
		return;
	}
	update();
	if (attackableObjects.empty()){
		if (selectedSkill->isType(CreatureSkill::WEAPON)){
			auto &weapons = engine::playerHandler.getPlayerCreature()->inventory.getEquippedWeapons();
			if (weapons.at(0)->type == GameObject::WEAPON_MELEE){
				engine::gui.log.addMessage("Nothing to attack.");
			}
			else if (weapons.at(0)->type == GameObject::WEAPON_RANGED){
				engine::gui.log.addMessage("Nothing to shoot at.");
			}
		}
		else if (selectedSkill->isType(CreatureSkill::MAGIC)){
			if (attackableObjects.empty()){
				engine::gui.log.addMessage("No targets.");
			}
		}
	}
}

void ActionExecutionFrame::init(Rectangle &bounds){
	GuiFrame::init(bounds);
	gameObjectDisplayBounds = Rectangle(getWidth(), getHeight());
}

void ActionExecutionFrame::setSkillAndAction(CreatureSkill &skill, CreatureAction &action){
	selectedSkill = &skill;
	selectedAction = &action;
}
