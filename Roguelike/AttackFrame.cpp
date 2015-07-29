#include "AttackFrame.h"
#include "KeyMapping.h"
#include "Engine.h"
#include "Direction.h"

bool AttackFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == LEFT){
				if (objectIndex == 0) objectIndex = attackableObjects.size() - 1;
				else objectIndex--;
				updateTarget();
				handled = true;
			}
			else if (direction == RIGHT){
				if (objectIndex == attackableObjects.size() - 1) objectIndex = 0;
				else objectIndex++;
				updateTarget();
				handled = true;
			}
			else if (direction == CENTER){
				engine::playerHandler.getPlayerCreature()->attack(*attackableObjects.at(objectIndex));
				previouslyAttacked = attackableObjects.at(objectIndex);
				engine::requestUpdate = true;
				handled = true;
				close();
			}
		}
		if (!handled){
			handled = true;
			close();
		}
	}
	return handled;
}

void AttackFrame::render(){
	guiCreature.renderTo(*this);
	//cursor
	TCODConsole::root->setCharBackground(
		attackableObjects.at(objectIndex)->location.x - engine::camera.location.x,
		attackableObjects.at(objectIndex)->location.y - engine::camera.location.y,
		Gui::INSPECTION_CURSOR,
		TCOD_BKGND_ALPHA(Gui::INSPECTION_CURSOR_ALPHA));
}

void AttackFrame::setAttackableObjects(std::vector<std::shared_ptr<DynamicObject>> attackableObjects){
	this->attackableObjects = attackableObjects;
}

void AttackFrame::updateTarget(){
	guiCreature.setCurrentCreature(nullptr);
	if (attackableObjects.at(objectIndex)->type == Creature::CREATURE){
		auto &creature = static_cast<Creature&>(*attackableObjects.at(objectIndex));
		guiCreature.setCurrentCreature(&creature);
	}
}

void AttackFrame::onOpen(){
	int index = 0;	
	bool usePreviouslyAttackedIndex = false;
	for (auto &o : attackableObjects){
		if (o == previouslyAttacked){
			objectIndex = index;
			usePreviouslyAttackedIndex = true;
			break;
		}
		else index++;
	}	
	if (!usePreviouslyAttackedIndex){
		objectIndex = 0;
	}
	updateTarget();
}
