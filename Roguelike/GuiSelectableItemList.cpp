#include "GuiSelectableItemList.h"
#include "GuiFrame.h"
#include "Gui.h"
#include "ItemContainer.h"
#include "Direction.h"

void GuiSelectableItemList::setItemContainer(ItemContainer &container){
	itemContainer = &container;
	itemContainer->sort();
	selectedRow = 0;
	selectedOperation = 0;
	updateSelection();
}

void GuiSelectableItemList::setGetOperationsFunction(std::function<std::vector<std::string>(std::shared_ptr<Item>, bool)> getOperations){
	getOperationsFunction = getOperations;
}

void GuiSelectableItemList::setOnOperationSelectedFunction(std::function<void(std::shared_ptr<Item>, std::string)> onOperationSelected){
	onOperationSelectedFunction = onOperationSelected;
}

bool GuiSelectableItemList::handleKey(TCOD_key_t &key){
	bool handled = false;
	Point2D direction;
	if (!itemContainer->items.empty()){
		direction = KeyMapping::direction(key.vk);
		if (!direction.undefined()){
			if (direction == UP){
				if (selectedRow == 0) selectedRow = itemContainer->items.size() - 1;
				else selectedRow--;
				updateSelection();
				selectedOperation = 0;
				handled = true;
			}
			else if (direction == DOWN){
				if (selectedRow == itemContainer->items.size() - 1) selectedRow = 0;
				else selectedRow++;
				updateSelection();
				selectedOperation = 0;
				handled = true;
			}
			else if (direction == LEFT){
				if (selectedOperation == 0) selectedOperation = operationsForSelectedItem.size() - 1;
				else selectedOperation--;
				handled = true;
			}
			else if (direction == RIGHT){
				if (selectedOperation == operationsForSelectedItem.size() - 1) selectedOperation = 0;
				else selectedOperation++;
				handled = true;
			}
			else if (direction == CENTER){
				onOperationSelectedFunction(itemContainer->getAt(selectedRow), operationsForSelectedItem[selectedOperation]);
				updateSelection();
				handled = true;
			}
		}
	}
	return handled;
}

void GuiSelectableItemList::updateSelection(){
	if (!itemContainer->items.empty()){
		if (selectedRow > (int)(itemContainer->items.size() - 1)){
			--selectedRow;
		}
		operationsForSelectedItem = getOperationsFunction(itemContainer->getAt(selectedRow), true);
		if (selectedOperation > (int)(operationsForSelectedItem.size() - 1)) selectedOperation = 0;
	}
}

void GuiSelectableItemList::renderTo(GuiFrame &frame, Rectangle &bounds){
	//No items
	if (itemContainer->items.empty()){
		frame.printString(
			bounds.start.x, bounds.start.y + bounds.getHeight() / 2,
			bounds.getWidth(), 0,
			Gui::FRAME_FG,
			TCOD_CENTER,
			"No items");
	}
	else{
		//Items
		int startIndex = selectedRow;
		if (startIndex > (int)(itemContainer->items.size() - bounds.getHeight() - 1)){
			startIndex = itemContainer->items.size() - bounds.getHeight() - 1;
			if (startIndex < 0) startIndex = 0;
		}
		int endIndex = startIndex + bounds.getHeight();
		if (endIndex >(int)(itemContainer->items.size() - 1)){
			endIndex = itemContainer->items.size() - 1;
		}
		auto &iterator = itemContainer->items.begin();
		std::advance(iterator, startIndex);
		int offsetY = 0;
		for (int index = startIndex; index <= endIndex; ++index){
			auto item = *iterator;
			//description
			frame.printString(
				bounds.start.x, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				item->rarity.color * Gui::RARITY_COLOR_MULTIPLIER, 
				TCOD_LEFT,
				item->getDescription());
			//stats
			frame.printString(
				bounds.start.x + bounds.getWidth() / 2, bounds.start.y + offsetY,
				bounds.getWidth(), 0,
				Gui::FRAME_FG,
				TCOD_LEFT, 
				item->getStatistics());
			//operator
			if (index == selectedRow){
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					Gui::SELECTABLE_OPERATION,
					TCOD_RIGHT,
					operationsForSelectedItem.at(selectedOperation));
				//row bg
				frame.paintBg(bounds.start.x, bounds.start.y + offsetY, bounds.getWidth(), 0, Gui::SELECTABLE_BG);
			}
			else{
				frame.printString(
					bounds.start.x, bounds.start.y + offsetY,
					bounds.getWidth(), 0,
					Gui::SELECTABLE_OPERATION,
					TCOD_RIGHT,
					getOperationsFunction(item, false).at(0));
			}
			++offsetY;
			++iterator;
		}
	}
}
