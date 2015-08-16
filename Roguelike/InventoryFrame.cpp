#include "InventoryFrame.h"
#include "Engine.h"
#include "String.h"

void InventoryFrame::onOpen(){
	guiSelectableItemList.setItemContainer(engine::playerHandler.getPlayerCreature()->inventory.items);
}

bool InventoryFrame::handleKey(TCOD_key_t &key){
	bool handled = false;
	if (!isOpen){
		handled = GuiFrame::handleKey(key);
	}
	else{
		handled = guiSelectableItemList.handleKey(key);
		if (!handled){
			close();
			handled = true;
		}
	}
	return handled;
}

void InventoryFrame::render(){
	GuiFrame::render();
	guiTopBox.renderTo(*this, guiTopBoxBounds);
	//currency
	printString(
		guiTopBoxBounds.start.x, guiTopBoxBounds.start.y,
		guiTopBoxBounds.getWidth(), 0,
		Gui::FRAME_FG, 
		TCOD_LEFT, 
		engine::string.currency(engine::playerHandler.getPlayerCreature()->inventory.currency));
	//weightKg
	printString(
		guiTopBoxBounds.start.x, guiTopBoxBounds.start.y,
		guiTopBoxBounds.getWidth() - 6, 0,
		Gui::FRAME_FG, 
		TCOD_RIGHT, 
		engine::string.weightKg(engine::playerHandler.getPlayerCreature()->inventory.getTotalWeight()));
	guiDisplayBox.renderTo(*this, guiDisplayBoxBounds);
	guiGameObjectDisplay.renderTo(*this, guiGameObjectDisplayBounds);
	guiSelectableItemList.renderTo(*this, guiSelectableItemListBounds);
	blit();
}

void InventoryFrame::init(Rectangle bounds){
	GuiFrame::init(bounds);
	guiTopBoxBounds = Rectangle(Point2D(0, 0), Point2D(bounds.getWidth(), 3));
	guiDisplayBoxBounds = Rectangle(Point2D(0, 3), Point2D(bounds.getWidth(), 14));
	guiGameObjectDisplayBounds = Rectangle(Point2D(0, 3), Point2D(getWidth(), 14));
	guiSelectableItemListBounds = Rectangle(Point2D(0, 14), Point2D(getWidth(), getHeight() - 14));
	guiSelectableItemList.setGetOperationsFunction(
		[this](std::shared_ptr<Item> item, bool selected) -> std::vector<std::string>{
		if (selected){
			//update item in display
			guiGameObjectDisplay.setDisplayedObject(item.get());
		}
		if (engine::playerHandler.getPlayerCreature()->inventory.isEquipped(item)){
			if (selected){			
				if (item->isWeapon() || item->isArmor()) return EQUIPMENT_UNEQUIP_OPERATIONS;
				else if (item->isConsumable()) return CONSUMABLE_OPERATIONS;
				else return{ "Error" };
			}
			else return {"Equipped"};
		}
		else{
			if (selected){
				if (item->isWeapon() || item->isArmor()) return EQUIPMENT_EQUIP_OPERATIONS;
				else if (item->isConsumable()) return CONSUMABLE_OPERATIONS;
				else return { "Error" };
			}
			else return { "" };
		}
	});
	guiSelectableItemList.setOnOperationSelectedFunction(
		[this](std::shared_ptr<Item> item, std::string operation){
		if (operation == EQUIP){
			if (!engine::playerHandler.getPlayerCreature()->inventory.equip(item)){
				if (item->isWeapon()){
					engine::gui.log.addMessage("I am holding too much.");
				}
				else if (item->isArmor()){
					engine::gui.log.addMessage("I am wearing too much.");
				}
			}
		}
		else if (operation == UNEQUIP) engine::playerHandler.getPlayerCreature()->inventory.unequip(item);
		else if (operation == CONSUME) engine::playerHandler.getPlayerCreature()->inventory.consume(std::static_pointer_cast<Consumable>(item));
		else if (operation == DROP) engine::playerHandler.getPlayerCreature()->inventory.drop(item);
		//clear display
		guiGameObjectDisplay.clear();
	});
}
