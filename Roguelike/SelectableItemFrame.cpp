#include "SelectableItemFrame.h"

bool SelectableItemFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
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

void SelectableItemFrame::render(float elapsed){
	//Frame
	GuiFrame::render(elapsed);

	if (items.items.empty()){
		console->printRectEx(console->getWidth() / 2, console->getHeight() / 2, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_CENTER, "No items");
	}

	blit();

	if (!items.items.empty()){
		//Items
		int y = 0;
		for (auto &item : items.items){
			if (y == selectedRow) console->setDefaultForeground(selectionColor);
			else console->setDefaultForeground(FG_COLOR);
			//Item
			console->printRectEx(1, y + 1, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_LEFT, item->getDescription().c_str());
			//Operation
			if (y == selectedRow){
				console->printRectEx(console->getWidth() - 2, y + 1, console->getWidth(), 1, TCOD_BKGND_NONE, TCOD_RIGHT, operations[selectedOperation].c_str());
			}

			blit(1, y + 1, console->getWidth() - 1, 1, bounds.start.x + 1, bounds.start.y + y + 1, alphaFg, alphaBg);
			++y;
		}
	}
}

void SelectableItemFrame::addItem(std::shared_ptr<Item> &item){
	items.add(item);
}

void SelectableItemFrame::removeItem(std::shared_ptr<Item> &item){
	items.remove(*item);
	if (items.items.size() == 0) close();
	else if (selectedRow > items.items.size() - 1) selectedRow--;
	selectedOperation = 0;
}

void SelectableItemFrame::removeAll(){
	items.items.clear();
}

void SelectableItemFrame::onOpen(){
	selectedRow = 0;
	selectedOperation = 0;
	if (!items.items.empty()) operations = getOperationsForItem(items.items.at(0));
}