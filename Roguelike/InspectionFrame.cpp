#include "InspectionFrame.h"
#include "KeyMapping.h"
#include "Engine.h"

bool InspectionFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			Point2D newLocation = inspectorLocation + direction;
			if (newLocation.x >= 0 && newLocation.x < Engine::camera.getWidth() &&
				newLocation.y >= 0 && newLocation.y < Engine::camera.getHeight()){
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

void InspectionFrame::render(float elapsed){
	std::string description = "";
	Point2D pointInMap = inspectorLocation + Engine::camera.location;
	GameObject *objectInCursor = nullptr;

	if (Engine::playerController.playerCreature->inFov(pointInMap.x, pointInMap.y)){
		GuiFrame::render(elapsed);

		std::vector<std::shared_ptr<DynamicObject>> dynamicObjects = Engine::area.getDynamicObjectsAt(pointInMap);
		if (!dynamicObjects.empty()){
			objectInCursor = dynamicObjects.at(0).get();
		}
		else{
			std::vector<std::shared_ptr<Item>> items = Engine::area.getItemsAt(pointInMap);
			if (!items.empty()){
				objectInCursor = items[0].get();
			}
			else{
				objectInCursor = Engine::area.staticObjects[pointInMap.x][pointInMap.y].get();
			}
		}
		if (objectInCursor != nullptr) description = objectInCursor->getDescription();
		console->printRect(1, 1, console->getWidth() - 2, 1, description.c_str());

		blit();
	}

	//Inspector cursor
	TCODConsole::root->setCharBackground(inspectorLocation.x, inspectorLocation.y, inspectorColor, TCOD_BKGND_ALPHA(0.5));
}

void InspectionFrame::onOpen(){
	inspectorLocation.x = Engine::camera.getWidth() / 2;
	inspectorLocation.y = Engine::camera.getHeight() / 2;
}