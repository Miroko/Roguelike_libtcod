#include "HelpFrame.h"


bool HelpFrame::handleKey(TCOD_key_t key, bool &requireUpdate){
	bool handled = GuiFrame::handleKey(key, requireUpdate);
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