#include "SelectableItemFrame.h"
#include "Direction.h"

bool SelectableItemFrame::handleKey(TCOD_key_t key){
	Point2D direction;
	switch (key.vk) {
	case TCODK_KP8: direction = UP; break;
	case TCODK_KP2: direction = DOWN; break;
	case TCODK_KP5: direction = CENTER; break;
	default: break;
	}

	if (!direction.undefined()){
		if (direction == UP && selectedRow > 0) selectedRow--;
		else if (direction == DOWN && selectedRow < items.items.size() - 1) selectedRow++;
		else if (direction == CENTER){
			onItemSelect(items.items.at(selectedRow));
		}
	}
	else if (key.pressed){
		openClose();
	}

	return true;
}

void SelectableItemFrame::render(float elapsed){
	//Frame
	GuiFrame::render(elapsed);
	blit();

	//Items
	int y = 0;
	for (auto &item : items.items){
		if (y == selectedRow) console->setDefaultForeground(selectionColor);
		else console->setDefaultForeground(FG_COLOR);
		console->printRectEx(1, y + 1, console->getWidth(), 1, TCOD_BKGND_SET, TCOD_LEFT, item->name.c_str());
		blit(1, y + 1, console->getWidth() - 1, 1, bounds.start.x + 1, bounds.start.y + y + 1, alphaFg, alphaBg);
		++y;
	}
}

void SelectableItemFrame::openClose(){
	GuiFrame::openClose();
	selectedRow = 0;
}