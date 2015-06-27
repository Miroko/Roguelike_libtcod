#include "DialogFrame.h"
#include "KeyMapping.h"
#include "Direction.h"


void DialogFrame::setDialog(std::shared_ptr<Dialog> dialog){
	currentDialog = dialog;
	selectedOption = 0;
}

bool DialogFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
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

void DialogFrame::render(){
	GuiFrame::render();

	//Text
	printString(0, 0, getWidth(), getHeight(), FG_COLOR, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, currentDialog->getText().c_str());

	//Options
	int offsetY = 0;
	for (auto &option : currentDialog->dialogOptions){
		if (offsetY == selectedOption){
			printString(0, getHeight() - offsetY, getWidth(), 1, selectionColor, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, currentDialog->dialogOptions.at(offsetY)->optionText.c_str());
		}
		else{
			printString(0, getHeight() - offsetY, getWidth(), 1, FG_COLOR, FG_COLOR, TCOD_LEFT, TCOD_BKGND_NONE, currentDialog->dialogOptions.at(offsetY)->optionText.c_str());
		}
		++offsetY;
	}
	blit();
}