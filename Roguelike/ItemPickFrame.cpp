#include "ItemPickFrame.h"
#include "Engine.h"

bool ItemPickFrame::moveToInventory(std::shared_ptr<Item> &item){
	if (engine::playerHandler.playerInventory.getCurrentWeight() + item->weight > engine::objectLibrary.maxWeight){
		engine::gui.log.addMessage("I need to drop something first.");
	}
	else{
		engine::areaHandler.getCurrentArea()->removeItem(item);
		engine::playerHandler.getPlayerCreature()->inventory.items.add(item);
		guiSelectableItemList.itemContainer->remove(item);
	}
	return true;
}

bool ItemPickFrame::handleKey(TCOD_key_t &key){
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

void ItemPickFrame::render(){
	GuiFrame::render();
	guiDisplayBox.renderTo(*this, guiDisplayBoxBounds);
	guiGameObjectDisplay.renderTo(*this, guiGameObjectDisplayBounds);
	guiSelectableItemList.renderTo(*this, guiSelectableItemListBounds);
	blit();
}

void ItemPickFrame::init(Rectangle bounds){
	GuiFrame::init(bounds);
	guiDisplayBoxBounds = Rectangle(Point2D(0, 0), Point2D(bounds.getWidth(), 11));
	guiGameObjectDisplayBounds = Rectangle(Point2D(0, 0), Point2D(getWidth(), 11));
	guiSelectableItemListBounds = Rectangle(Point2D(0, 11), Point2D(getWidth(), getHeight() - 11));
	guiSelectableItemList.setGetOperationsFunction(
		[this](std::shared_ptr<Item> item, bool selected) -> std::vector<std::string>{
		if (selected){
			//update item in display
			guiGameObjectDisplay.setDisplayedObject(item.get());
			return PICK_OPERATIONS;
		}
		else{
			return { "" };
		}
	});
	guiSelectableItemList.setOnOperationSelectedFunction(
		[this](std::shared_ptr<Item> item, std::string operation){
		moveToInventory(item);
		//clear display
		guiGameObjectDisplay.clear();
	});
}

void ItemPickFrame::onOpen(){
	guiSelectableItemList.setItemContainer(engine::playerHandler.playerInventory.temporary);
}

void ItemPickFrame::onClose(){
	engine::playerHandler.playerInventory.temporary.removeAll();
}