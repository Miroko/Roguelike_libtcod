#include "InspectionFrame.h"
#include "KeyMapping.h"
#include "Engine.h"
#include "Weapon.h"

bool InspectionFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			Point2D newLocation = inspectorLocation + direction;
			if (newLocation.x >= 0 && newLocation.x < engine::camera.getWidth() &&
				newLocation.y >= 0 && newLocation.y < engine::camera.getHeight()){
				inspectorLocation = newLocation;
			}
			handled = true;
		}
		if (!handled){
			close();
			handled = true;
		}
	}
	return handled;
}

void InspectionFrame::render(){
	engine::gui.guiCreature.close();
	engine::gui.guiWeapon.close();
	Point2D pointInMap = inspectorLocation + engine::camera.location;
	if (engine::playerHandler.getPlayerCreature()->ai->inFov(pointInMap)){
		std::vector<std::shared_ptr<Creature>*> creatures = engine::areaHandler.getCurrentArea()->getCreatures(pointInMap);	
		if (!creatures.empty()){
			engine::gui.guiCreature.open();
			engine::gui.guiCreature.setCurrentCreature(*creatures.front()->get());
		}
		else{
			std::vector<std::shared_ptr<Item>*> items = engine::areaHandler.getCurrentArea()->getItemsAt(pointInMap);
			if (!items.empty()){
				Item *item = items.front()->get();
				if (item->isWeapon()){
					engine::gui.guiWeapon.open();
					engine::gui.guiWeapon.setCurrentWeapon(static_cast<Weapon&>(*item));
				}
			}
		}
	}

	//Inspector cursor
	TCODConsole::root->setCharBackground(inspectorLocation.x, inspectorLocation.y, inspectorColor, TCOD_BKGND_ALPHA(0.5));
}

void InspectionFrame::onClose(){
	engine::gui.guiCreature.close();
	engine::gui.guiWeapon.close();
}

void InspectionFrame::onOpen(){
	inspectorLocation.x = engine::camera.getWidth() / 2;
	inspectorLocation.y = engine::camera.getHeight() / 2;
}