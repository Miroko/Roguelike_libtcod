#include "SelectableItemFrame.h"
#include "RarityType.h"
#include "String.h"
#include "Engine.h"

void SelectableItemFrame::setItemContainer(ItemContainer &itemContainer){
	currentItemContainer = &itemContainer;
}

bool SelectableItemFrame::handleKey(TCOD_key_t &key){
	bool handled = GuiFrame::handleKey(key);
	if (isOpen){
		Point2D direction;
		if (!currentItemContainer->items.empty()){
			direction = KeyMapping::direction(key.vk);
			if (!direction.undefined()){
				if (direction == UP){
					if (selectedRow == 0) selectedRow = currentItemContainer->items.size() - 1;
					else selectedRow--;
					operations = getOperationsForItem(currentItemContainer->getAt(selectedRow));
					selectedOperation = 0;
					handled = true;
				}
				else if (direction == DOWN){
					if (selectedRow == currentItemContainer->items.size() - 1) selectedRow = 0;
					else selectedRow++;
					operations = getOperationsForItem(currentItemContainer->getAt(selectedRow));
					selectedOperation = 0;
					handled = true;
				}
				else if (direction == LEFT){
					if (selectedOperation == 0) selectedOperation = operations.size() - 1;
					else selectedOperation--;
					handled = true;
				}
				else if (direction == RIGHT){
					if (selectedOperation == operations.size() - 1) selectedOperation = 0;
					else selectedOperation++;
					handled = true;
				}
				else if (direction == CENTER){
					onItemSelect(currentItemContainer->getAt(selectedRow), operations[selectedOperation]);
					updateSelection();
					handled = true;
				}
			}
		}
		if (!handled){
			close();
			handled = true;
		}		
	}
	return handled;
}

void SelectableItemFrame::render(){
	GuiFrame::render();
	
	//No items
	if (currentItemContainer->items.empty()){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 2, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_CENTER, "No items");
	}
	else{
		//Items
		int offsetY = 0;
		for (auto &item : currentItemContainer->items){
			//item
			printString(0, offsetY, getWidth(), 1, item->rarity.color, item->rarity.color, TCOD_LEFT, TCOD_BKGND_NONE, item->name);
			//stats
			printString(getWidth() / 2, offsetY, getWidth(), 1, FG_COLOR, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, item->getStatistics() + engine::string.currency(item->getValue()) + " " + engine::string.weight(item->weight));
			//operator
			if (offsetY == selectedRow){
				printString(0, offsetY, getWidth(), 1, OPERATION_COLOR, OPERATION_COLOR, TCOD_RIGHT, TCOD_BKGND_NONE, operations.at(selectedOperation));
				paintRowBg(SELECTION_COLOR, selectedRow);
			}
			++offsetY;
		}
	}

	blit();
}

void SelectableItemFrame::paintRowBg(const TCODColor &color, int row){
	if (!currentItemContainer->items.empty()){
		for (int x = 1; x <= console->getWidth() - 2; x++){
			console->setCharBackground(x, row + MARGIN + 1, color);
		}
	}
}

void SelectableItemFrame::updateSelection(){
	if (currentItemContainer->items.size() == 0) close();
	else {
		if(selectedRow >= (int)currentItemContainer->items.size()) selectedRow = currentItemContainer->items.size() - 1;
		operations = getOperationsForItem(currentItemContainer->getAt(selectedRow));
		selectedOperation = 0;
	}
}

void SelectableItemFrame::onOpen(){
	GuiFrame::onOpen();
	selectedRow = 0;
	selectedOperation = 0;
	if (!currentItemContainer->items.empty()) operations = getOperationsForItem(currentItemContainer->getAt(0));
}