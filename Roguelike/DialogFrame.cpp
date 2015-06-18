#include "DialogFrame.h"
#include "KeyMapping.h"
#include "Direction.h"

void DialogFrame::setDialog(std::shared_ptr<Dialog> dialog){
	currentDialog = dialog;
	selectedOption = 0;
}

bool DialogFrame::handleKey(TCOD_key_t key){
	bool handled = false;
	if (isOpen){
		Point2D direction;
		if (!currentDialog->dialogOptions.empty()){
			direction = KeyMapping::direction(key.vk);
			if (!direction.undefined()){
				if (direction == UP){
					if (selectedOption == currentDialog->dialogOptions.size() - 1) selectedOption = 0;
					else selectedOption++;
					handled = true;
				}
				else if (direction == DOWN){
					if (selectedOption == 0) selectedOption = currentDialog->dialogOptions.size() - 1;
					else selectedOption--;
					handled = true;
				}
				else if (direction == CENTER){
					currentDialog = currentDialog->getNextDialog(currentDialog->dialogOptions.at(selectedOption));
					if (currentDialog == DIALOG_END) close();
					else selectedOption = 0;
					handled = true;
				}
			}
		}
	}
	if (!handled && isOpen){
		close();
		handled = true;
	}
	return handled;
}

void DialogFrame::render(float elapsed){
	GuiFrame::render(elapsed);

	//Text
	console->printRectEx(2, 2, console->getWidth() - 4, console->getHeight(), TCOD_BKGND_NONE, TCOD_LEFT,
			                                    currentDialog->getText().c_str());
	blit();

	//Options
	int y = 0;
	for (auto &option : currentDialog->dialogOptions){
		if (y == selectedOption) console->setDefaultForeground(selectionColor);
		else console->setDefaultForeground(FG_COLOR);
		console->printRectEx(2, console->getHeight() - 3 - y, console->getWidth(), 1, TCOD_BKGND_NONE, TCOD_LEFT,
				                             currentDialog->dialogOptions.at(y)->optionText.c_str());

		blit(2, console->getHeight() - 3 - y, console->getWidth() - 4, 1, bounds.start.x + 2, bounds.end.y - y - 3, alphaFg, alphaBg);
		++y;
	}
}