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
	//Inspector cursor
	TCODConsole::root->setCharBackground(inspectorLocation.x, inspectorLocation.y,
		Gui::INSPECTION_CURSOR,
		TCOD_BKGND_ALPHA(Gui::INSPECTION_CURSOR_ALPHA));
}

void InspectionFrame::updateSelection(){
	engine::gui.guiCreature.close();
	engine::gui.guiWeapon.close();
	engine::gui.guiArmor.close();
	engine::gui.guiPotion.close();
	engine::gui.guiTile.close();
	engine::gui.guiOperatable.close();

	Point2D cursorLocationInArea = inspectorLocation + engine::camera.location;
	if (engine::playerHandler.getPlayerCreature()->ai->inFov(cursorLocationInArea)){
		std::vector<std::shared_ptr<Creature>*> creatures = engine::areaHandler.getCurrentArea()->getCreatures(cursorLocationInArea);
		if (!creatures.empty()){
			engine::gui.guiCreature.open();
			engine::gui.guiCreature.setCurrentCreature(*creatures.front()->get());
		}
		else{
			std::vector<std::shared_ptr<Item>*> items = engine::areaHandler.getCurrentArea()->getItemsAt(cursorLocationInArea);
			if (!items.empty()){
				Item *item = items.front()->get();
				if (item->isWeapon()){
					engine::gui.guiWeapon.open();
					engine::gui.guiWeapon.setCurrentWeapon(static_cast<Weapon&>(*item));
				}
				else if (item->isArmor()){
					engine::gui.guiArmor.open();
					engine::gui.guiArmor.setCurrentArmor(static_cast<Armor&>(*item));
				}
				else if (item->type == Item::POTION){
					engine::gui.guiPotion.open();
					engine::gui.guiPotion.setCurrentPotion(static_cast<Potion&>(*item));
				}
			}
			else{
				std::vector<std::shared_ptr<OperatableObject>*> operatables = engine::areaHandler.getCurrentArea()->getOperatables(cursorLocationInArea);
				if (!operatables.empty()){
					engine::gui.guiOperatable.open();
					engine::gui.guiOperatable.setCurrentOperatable(*operatables.front()->get());
				}
				else{
					Tile *tile = engine::areaHandler.getCurrentArea()->getTile(cursorLocationInArea);
					if (tile != nullptr){
						engine::gui.guiTile.open();
						engine::gui.guiTile.setCurrentTile(*tile);
					}
				}
			}
		}
	}
}

void InspectionFrame::onClose(){
	engine::gui.guiCreature.close();
	engine::gui.guiWeapon.close();
	engine::gui.guiArmor.close();
	engine::gui.guiPotion.close();
	engine::gui.guiTile.close();
	engine::gui.guiOperatable.close();
}

void InspectionFrame::onOpen(){
	inspectorLocation.x = engine::camera.getWidth() / 2;
	inspectorLocation.y = engine::camera.getHeight() / 2;
	updateSelection();
}
