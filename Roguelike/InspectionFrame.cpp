#include "InspectionFrame.h"
#include "KeyMapping.h"
#include "Engine.h"
#include "Weapon.h"
#include "Armor.h"

bool InspectionFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			Point2D newLocation = inspectorLocation + direction;
			if (newLocation.x >= 0 && newLocation.x < engine::camera.getWidth() &&
				newLocation.y >= 0 && newLocation.y < engine::camera.getHeight()){
				inspectorLocation = newLocation;
				updateSelection();
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
	GuiFrame::render();
	guiGameObjectDisplay.renderTo(*this, guiGameObjectDisplayBounds);
	//Inspector cursor
	TCODConsole::root->setCharBackground(inspectorLocation.x, inspectorLocation.y,
		Gui::INSPECTION_CURSOR,
		TCOD_BKGND_ALPHA(Gui::INSPECTION_CURSOR_ALPHA));
	blit();
}

void InspectionFrame::updateSelection(){
	//set new selection
	Point2D cursorLocationInArea = inspectorLocation + engine::camera.location;
	if (engine::playerHandler.getPlayerCreature()->ai->inFov(cursorLocationInArea)){
		std::vector<std::shared_ptr<Creature>*> creatures = engine::areaHandler.getCurrentArea()->getCreatures(cursorLocationInArea);
		if (!creatures.empty()){
			guiGameObjectDisplay.setDisplayedObject(creatures.front()->get());
		}
		else{
			std::vector<std::shared_ptr<Item>*> items = engine::areaHandler.getCurrentArea()->getItemsAt(cursorLocationInArea);
			if (!items.empty()){
				guiGameObjectDisplay.setDisplayedObject(items.front()->get());
			}
			else{
				std::vector<std::shared_ptr<OperatableObject>*> operatables = engine::areaHandler.getCurrentArea()->getOperatables(cursorLocationInArea);
				if (!operatables.empty()){
					guiGameObjectDisplay.setDisplayedObject(operatables.front()->get());
				}
				else{
					Tile *tile = engine::areaHandler.getCurrentArea()->getTile(cursorLocationInArea);
					if (tile != nullptr){
						guiGameObjectDisplay.setDisplayedObject(tile);
					}
					else{
						//not in fov
						guiGameObjectDisplay.clear();
					}
				}
			}
		}
	}
}

void InspectionFrame::onOpen(){
	inspectorLocation.x = engine::camera.getWidth() / 2;
	inspectorLocation.y = engine::camera.getHeight() / 2;
	updateSelection();
}

void InspectionFrame::init(Rectangle bounds){
	GuiFrame::init(bounds);
	guiGameObjectDisplayBounds = Rectangle(getWidth(), getHeight());
}