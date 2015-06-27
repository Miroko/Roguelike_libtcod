#include "SelectableItemFrame.h"
#include "RarityType.h"
#include "String.h"

bool SelectableItemFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	bool handled = GuiFrame::handleKey(key, requireUpdate);
	if (isOpen){
		Point2D direction;
		if (!items.items.empty()){
			direction = KeyMapping::direction(key.vk);
			if (!direction.undefined()){
				if (direction == UP){
					if (selectedRow == 0) selectedRow = items.items.size() - 1;
					else selectedRow--;
					operations = getOperationsForItem(items.items.at(selectedRow));
					selectedOperation = 0;
					handled = true;
				}
				else if (direction == DOWN){
					if (selectedRow == items.items.size() - 1) selectedRow = 0;
					else selectedRow++;
					operations = getOperationsForItem(items.items.at(selectedRow));
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
					onItemSelect(items.items.at(selectedRow), operations[selectedOperation]);
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
	if (items.items.empty()){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 2, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_CENTER, "No items");
	}
	else{
		//Items
		int offsetY = 0;
		for (auto &item : items.items){
			//item
			printString(0, offsetY, getWidth(), 1, item->rarity->color, item->rarity->color, TCOD_LEFT, TCOD_BKGND_NONE, item->name);
			//stats
			printString(0, offsetY, getWidth(), 1, FG_COLOR, FG_COLOR, TCOD_CENTER, TCOD_BKGND_NONE, item->getStatistics() + std::to_string(item->getValue()) + "c " + String::weight(item->weight));
			//operator
			if (offsetY == selectedRow){
				printString(0, offsetY, getWidth(), 1, OPERATION_COLOR, OPERATION_COLOR, TCOD_RIGHT, TCOD_BKGND_NONE, operations.at(selectedOperation));
				renderSelection();
			}
			++offsetY;
		}
	}

	blit();
}

void SelectableItemFrame::renderSelection(){
	if (!items.items.empty()){
		for (int x = 1; x <= console->getWidth() - 2; x++){
			console->setCharBackground(x, selectedRow + MARGIN + 1, SELECTION_COLOR);
		}
	}
}

void SelectableItemFrame::addItem(std::shared_ptr<Item> &item){
	items.add(item);
}

void SelectableItemFrame::removeItem(std::shared_ptr<Item> &item){
	items.remove(*item);
	if (selectedRow > items.items.size() - 1) selectedRow--;
	if (items.items.size() == 0) close();
	else{
		operations = getOperationsForItem(items.items.at(selectedRow));
		selectedOperation = 0;
	}
}

void SelectableItemFrame::removeAll(){
	items.items.clear();
}

void SelectableItemFrame::onOpen(){
	selectedRow = 0;
	selectedOperation = 0;
	if (!items.items.empty()) operations = getOperationsForItem(items.items.at(0));
}