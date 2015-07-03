#include "HelpFrame.h"


bool HelpFrame::handleKey(TCOD_key_t key){
	bool handled = GuiFrame::handleKey(key);
	if (!handled && isOpen){
		close();
		handled = true;
	}
	return handled;
}

void HelpFrame::render(){
	GuiFrame::render();

	blit();
}