#include "AttackFrame.h"
#include "KeyMapping.h"
#include "Engine.h"

void AttackFrame::setAttackableObjects(std::vector<std::shared_ptr<DynamicObject>> attackableObjects){
	this->attackableObjects = attackableObjects;
}

bool AttackFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	bool handled = GuiFrame::handleKey(key, requireUpdate);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == LEFT){
				if (objectIndex == 0) objectIndex = attackableObjects.size() - 1;
				else objectIndex--;
				handled = true;
			}
			else if (direction == RIGHT){
				if (objectIndex == attackableObjects.size() - 1) objectIndex = 0;
				else objectIndex++;
				handled = true;
			}
			else if (direction == CENTER){
				Engine::playerController.playerCreature->attackRanged(attackableObjects.at(objectIndex));
				close();
				handled = true;
				requireUpdate = true;
				previouslyAttacked = attackableObjects.at(objectIndex);
			}
		}
		if (!handled){
			close();
			handled = true;
		}
	}
	return handled;
}

void AttackFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	std::shared_ptr<DynamicObject> selectedObject = attackableObjects.at(objectIndex);

	console->printRect(1, 1, console->getWidth() - 2, 1, selectedObject->getDescription().c_str());

	blit();	

	attackLocation = selectedObject->location;
	TCODConsole::root->setCharBackground(attackLocation.x - Engine::camera.location.x, attackLocation.y - Engine::camera.location.y,
		cursorColor, TCOD_BKGND_ALPHA(0.5));
}

void AttackFrame::onOpen(){
	int index = 0;	
	for (auto &o : attackableObjects){
		if (o == previouslyAttacked){
			objectIndex = index;
			return;
		}
		index++;
	}	
	objectIndex = 0;
}
