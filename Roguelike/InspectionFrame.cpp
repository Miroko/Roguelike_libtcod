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
	updateSelection();
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
		auto &areaContainer = engine::areaHandler.getCurrentArea()->areaContainers[cursorLocationInArea.x][cursorLocationInArea.y];
		if (areaContainer.creature){
			guiGameObjectDisplay.setDisplayedObject(areaContainer.creature);
		}
		else if (!areaContainer.items.empty()){
			guiGameObjectDisplay.setDisplayedObject(&areaContainer.getItemToRender(engine::areaHandler.getCurrentArea()->getItemRenderNumberCurrent()));
		}
		else if (areaContainer.operatableObject){
			guiGameObjectDisplay.setDisplayedObject(areaContainer.operatableObject);
		}
		else{
			guiGameObjectDisplay.setDisplayedObject(areaContainer.tile);
		}
	}
	else{
		//not in fov
		guiGameObjectDisplay.clear();
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